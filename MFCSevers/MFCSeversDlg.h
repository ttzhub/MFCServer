
// MFCSeversDlg.h: 头文件
//

#pragma once
#include "CSever.h"

class CSever;                  //一定要加上

// CMFCSeversDlg 对话框
class CMFCSeversDlg : public CDialogEx
{
// 构造
public:
	CMFCSeversDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCSEVERS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// 显示控件
	CEdit m_EditShow;
	// 端口号
	UINT m_Port;
	// 用户计数
	UINT m_UserCount;
	afx_msg void OnBnClickedBntopensever();
	// 用于打开服务器
	CSever *listenSocket;
	// 链表用于存储用户
	CPtrList m_clientList;
	// 用于标记服务器状态
	bool m_flg_connect;
	// 增加用户，响应用户请求
	bool AddClient();
	// 移除下线的用户
	bool RemoveClient(CSever* pSocket);
	// 获取数据
	bool RecvData(CSever* pSocket);
	// 更新事件日志
	bool UpdateEvent(CString str);
	// 字符转换
	bool WChar2MByte(LPCWSTR srcBuff, LPSTR destBuff, int nlen);
	// 发送消息给各个客户端
	bool SendMSG(CString str);
};
