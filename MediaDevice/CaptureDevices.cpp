#include "stdafx.h"
#include "CaptureDevices.h"


CaptureDevices::CaptureDevices()
    : m_eMonikerAudio(NULL),
      m_eMonikerVideo(NULL)
{
    CoInitialize(0);
    Enumerate();
}

CaptureDevices::~CaptureDevices()
{
    if(m_eMonikerAudio)
    {
        m_eMonikerAudio->Release();
        m_eMonikerAudio = NULL;
    }
    if(m_eMonikerVideo)
    {
        m_eMonikerVideo->Release();
        m_eMonikerVideo = NULL;
    }
    CoUninitialize();
}

HRESULT CaptureDevices::Enumerate()
{
    HRESULT hr = S_OK;
    
    ICreateDevEnum *enumDev;
    
    hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&enumDev));
    
    if(FAILED(hr))
    {
        m_sLastError = L"Could not create device enumerator";
        return hr;
    }
    
    hr = enumDev->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &m_eMonikerVideo, NULL);
    
    if(FAILED(hr))
    {
        printf("No video capture devices available");
    }
    
    hr = enumDev->CreateClassEnumerator(CLSID_AudioInputDeviceCategory, &m_eMonikerAudio, NULL);
    
    if(FAILED(hr))
    {
        printf("No audio capture devices available");
    }
    
    enumDev->Release();
    
    return hr;
}

HRESULT CaptureDevices::GetVideoDevices(vector<wstring> &videoDevices)
{
    if(!m_eMonikerVideo)
    {
        return E_FAIL;
    }
    
    IMoniker *pMoniker = NULL;
    wstring name;
    
    while(m_eMonikerVideo->Next(1, &pMoniker, NULL) == S_OK)
    {
        IPropertyBag *pPropBag;
        HRESULT hr = pMoniker->BindToStorage(0, 0, IID_PPV_ARGS(&pPropBag));
        if(FAILED(hr))
        {
            pMoniker->Release();
            continue;
        }
        
        VARIANT var;
        VariantInit(&var);
        
        hr = pPropBag->Read(L"FriendlyName", &var, 0);
        if(SUCCEEDED(hr))
        {
            name = var.bstrVal;
            VariantClear(&var);
        }
        
        pPropBag->Release();
        pMoniker->Release();
        
        if(!name.empty())
        {
            videoDevices.push_back(name);
        }
    }
    return 1;
}

HRESULT CaptureDevices::GetAudioDevices(vector<wstring> &audioDevices)
{
    if(!m_eMonikerAudio)
    {
        return E_FAIL;
    }
    
    IMoniker *pMoniker = NULL;
    wstring name;
    
    while(m_eMonikerAudio->Next(1, &pMoniker, NULL) == S_OK)
    {
        IPropertyBag *pPropBag;
        HRESULT hr = pMoniker->BindToStorage(0, 0, IID_PPV_ARGS(&pPropBag));
        if(FAILED(hr))
        {
            pMoniker->Release();
            continue;
        }
        
        VARIANT var;
        VariantInit(&var);
        
        hr = pPropBag->Read(L"FriendlyName", &var, 0);
        if(SUCCEEDED(hr))
        {
            name = var.bstrVal;
            VariantClear(&var);
        }
        
        pPropBag->Release();
        pMoniker->Release();
        
        if(!name.empty())
        {
            audioDevices.push_back(name);
        }
    }
    return 1;
}
