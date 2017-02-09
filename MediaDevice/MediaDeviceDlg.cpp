
// MediaDeviceDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MediaDevice.h"
#include "MediaDeviceDlg.h"
#include "afxdialogex.h"
#include "CaptureDevices.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMediaDeviceDlg �Ի���




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


// CMediaDeviceDlg ��Ϣ�������

BOOL CMediaDeviceDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    
    // ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
    //  ִ�д˲���
    SetIcon(m_hIcon, TRUE);         // ���ô�ͼ��
    SetIcon(m_hIcon, FALSE);        // ����Сͼ��
    
    // TODO: �ڴ���Ӷ���ĳ�ʼ������
    
    RefreshDevice();
    return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMediaDeviceDlg::OnPaint()
{
    if(IsIconic())
    {
        CPaintDC dc(this); // ���ڻ��Ƶ��豸������
        
        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
        
        // ʹͼ���ڹ����������о���
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;
        
        // ����ͼ��
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialogEx::OnPaint();
    }
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
