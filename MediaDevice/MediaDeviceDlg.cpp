
// MediaDeviceDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MediaDevice.h"
#include "MediaDeviceDlg.h"
#include "afxdialogex.h"
#include "CaptureDevices.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMediaDeviceDlg 对话框




CMediaDeviceDlg::CMediaDeviceDlg(CWnd *pParent /*=NULL*/)
    : CDialogEx(CMediaDeviceDlg::IDD, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMediaDeviceDlg::DoDataExchange(CDataExchange *pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT1, m_EditVideo);
    DDX_Control(pDX, IDC_EDIT2, m_EditAudio);
    DDX_Control(pDX, IDOK, m_BtnOK);
}

BEGIN_MESSAGE_MAP(CMediaDeviceDlg, CDialogEx)
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDOK, &CMediaDeviceDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMediaDeviceDlg 消息处理程序

BOOL CMediaDeviceDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    
    // 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
    //  执行此操作
    SetIcon(m_hIcon, TRUE);         // 设置大图标
    SetIcon(m_hIcon, FALSE);        // 设置小图标
    
    // TODO: 在此添加额外的初始化代码
    
    RefreshDevice();
    return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMediaDeviceDlg::OnPaint()
{
    if(IsIconic())
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
HCURSOR CMediaDeviceDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}


void CMediaDeviceDlg::RefreshDevice()
{
    m_BtnOK.EnableWindow(FALSE);
    
    CaptureDevices capDev;
    vector<wstring> videoDevices, audioDevices;
    capDev.GetVideoDevices(videoDevices);
    capDev.GetAudioDevices(audioDevices);
    
    CString vvv, aaa;
    for(UINT i = 0; i < videoDevices.size(); i++)
    {
        vvv.AppendFormat(L"%s\r\n", videoDevices[i].c_str());
    }
    m_EditVideo.SetWindowText(vvv);
    for(UINT i = 0; i < audioDevices.size(); i++)
    {
        aaa.AppendFormat(L"%s\r\n", audioDevices[i].c_str());
    }
    m_EditAudio.SetWindowText(aaa);
    
    m_BtnOK.EnableWindow(TRUE);
}

void CMediaDeviceDlg::OnBnClickedOk()
{
    RefreshDevice();
}
