
// MFCSeversDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MFCSevers.h"
#include "MFCSeversDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCSeversDlg 对话框



CMFCSeversDlg::CMFCSeversDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCSEVERS_DIALOG, pParent)
	, m_Port(1111)
	, m_UserCount(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCSeversDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EditShow, m_EditShow);
	DDX_Text(pDX, IDC_EditPort, m_Port);
	DDX_Text(pDX, IDC_UserCount, m_UserCount);
	DDV_MinMaxUInt(pDX, m_UserCount, 0, UINT_MAX);
}

BEGIN_MESSAGE_MAP(CMFCSeversDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BntOpenSever, &CMFCSeversDlg::OnBnClickedBntopensever)
END_MESSAGE_MAP()


// CMFCSeversDlg 消息处理程序

BOOL CMFCSeversDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCSeversDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCSeversDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCSeversDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCSeversDlg::OnBnClickedBntopensever()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_flg_connect)

	{
		delete listenSocket;
		listenSocket = NULL;
		m_flg_connect = false;
		SetDlgItemText(IDC_BntOpenSever, _T("打开服务器"));
		UpdateEvent(_T("系统关闭服务器."));
		return;
	}

	listenSocket = new CSever();
	listenSocket->m_SeverDlg = this;		// 指定对话框为主对话框，不能少了这句
	UpdateData(true);
	// 创建服务器的套接字，IP地址默认本机IP
	if (!listenSocket->Create(1111))		
	{
		AfxMessageBox(_T("创建套接字错误！"));
		listenSocket->Close();
		return;
	}
	// 开始监听
	if (!listenSocket->Listen())
	{
		AfxMessageBox(_T("监听失败！"));
		listenSocket->Close();
		return;
	}
	m_flg_connect = true;
	SetDlgItemText(IDC_BntOpenSever, _T("关闭服务器"));
	UpdateEvent(_T("系统打开服务器."));

}



// 增加用户，响应用户请求
bool CMFCSeversDlg::AddClient()
{
	// TODO: 在此处添加实现代码.
	CSever *pSocket = new CSever;
	pSocket->m_SeverDlg = this;		
	listenSocket->Accept(*pSocket);		// 捕获申请的Client的Socket
	pSocket->AsyncSelect(FD_READ | FD_WRITE | FD_CLOSE);
	m_clientList.AddTail(pSocket);		// 加入到clientList
	m_UserCount = m_clientList.GetCount();
	UpdateData(false);					// 更新静态文本显示
	UpdateEvent(_T("用户连接服务器."));
	SendMSG(_T("Hello!"));
	return false;
}


// 移除下线的用户
bool CMFCSeversDlg::RemoveClient(CSever* pSocket)
{
	// TODO: 在此处添加实现代码.
	POSITION nPos = m_clientList.GetHeadPosition();
	POSITION nTmpPos = nPos;
	while (nPos)
	{
		// GetNext(nPos)返回前一个位置
		CSever* pSockItem = (CSever*)m_clientList.GetNext(nPos);
		if (pSockItem->m_hSocket == pSocket->m_hSocket) // 需要删除的pSocket句柄与当前pSockItem的一致时删除
		{
			pSockItem->Close();		// 关闭需要关闭的Socket
			delete pSockItem;		// 清理指针
			m_clientList.RemoveAt(nTmpPos);		// 移除链表中的Socket
			m_UserCount = m_clientList.GetCount();
			UpdateData(false);
			UpdateEvent(_T("用户离开."));
			break;
			//return;
		}
		nTmpPos = nPos;
	}
	return false;
}


// 获取数据
bool CMFCSeversDlg::RecvData(CSever* pSocket)
{
	// TODO: 在此处添加实现代码.
	char* pData = NULL;
	pData = new char[1024];
	memset(pData, 0, sizeof(char) * 1024);
	UCHAR leng = 0;
	CString str;
	if (pSocket->Receive(pData, 1024, 0) != SOCKET_ERROR)
	{
		str = pData;
		//ControlPC(str);     // 依据指令控制电脑
		SendMSG(str);     // 转发数据给所有用户，包括发送数据的用户
	}
	delete pData;
	pData = NULL;
	return false;
}


// 更新事件日志
bool CMFCSeversDlg::UpdateEvent(CString str)
{
	// TODO: 在此处添加实现代码.
	CString string;
	CTime time = CTime::GetCurrentTime();
	// 获取系统当前时间
	str += _T("\r\n");
	// 用于换行显示日志
	string = time.Format(_T("%Y/%m/%d %H:%M:%S  ")) + str;
	// 格式化当前时间
	int lastLine = m_EditShow.LineIndex(m_EditShow.GetLineCount() - 1);
	//获取编辑框最后一行索引
	m_EditShow.SetSel(lastLine + 1, lastLine + 2, 0);
	//选择编辑框最后一行
	m_EditShow.ReplaceSel(string);                                                             //替换所选那一行的内容
	return false;

}


// 字符转换
bool CMFCSeversDlg::WChar2MByte(LPCWSTR srcBuff, LPSTR destBuff, int nlen)
{
	// TODO: 在此处添加实现代码.
	int n = 0;
	n = WideCharToMultiByte(CP_OEMCP, 0, srcBuff, -1, destBuff, 0, 0, FALSE);
	if (n < nlen)	return FALSE;
	WideCharToMultiByte(CP_OEMCP, 0, srcBuff, -1, destBuff, nlen, 0, FALSE);
	return TRUE;
}


// 发送消息给各个客户端
bool CMFCSeversDlg::SendMSG(CString str)
{
	// TODO: 在此处添加实现代码.
	int num = str.GetLength();
	char *pSend = new char[str.GetLength()];
	memset(pSend, 0, str.GetLength() * sizeof(char));
 	if (!WChar2MByte(str.GetBuffer(0), pSend, str.GetLength()))
 	{
 		AfxMessageBox(_T("字符转换失败"));
 		delete pSend;
		//str.ReleaseBuffer();
 		return false;
 	}
	//str.ReleaseBuffer();
	POSITION nPos = m_clientList.GetHeadPosition();
	while (nPos)
	{
		CSever* pTemp = (CSever*)m_clientList.GetNext(nPos);
		pTemp->Send(pSend, str.GetLength());
		//pTemp->Send(pSend, sizeof(pSend));
	}
	delete pSend;
	return true;
}
