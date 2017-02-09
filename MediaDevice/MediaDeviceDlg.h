
// MediaDeviceDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CMediaDeviceDlg 对话框
class CMediaDeviceDlg : public CDialogEx
{
// 构造
public:
    CMediaDeviceDlg(CWnd *pParent = NULL);  // 标准构造函数
    
// 对话框数据
    enum { IDD = IDD_MEDIADEVICE_DIALOG };
    
protected:
    virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV 支持
    
    
// 实现
protected:
    HICON m_hIcon;
    
    // 生成的消息映射函数
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()
public:
    CEdit m_EditVideo;
    CEdit m_EditAudio;
    afx_msg void OnBnClickedOk();
    void RefreshDevice();
    CButton m_BtnOK;
};
