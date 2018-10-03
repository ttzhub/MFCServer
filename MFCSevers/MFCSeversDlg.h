
// MFCSeversDlg.h: 头文件
//

#pragma once


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
};
