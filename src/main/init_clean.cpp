#include "main.h"

//-----------------------------------------------------------------------------
// Initierar Direct3D
//-----------------------------------------------------------------------------
HRESULT initD3D(HWND hWnd)
{
    //Skapa D3D objekt
    if(NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
        return E_FAIL;

    //---------------------------------
    // D3DDevice
    //---------------------------------

    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

    if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &d3dpp, &g_pd3dDevice)))
    {
        return E_FAIL;
    }

    //---------------------------------
    // Render och Sampler states
    //---------------------------------

    g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE); //Sätter på "Z-buffer"
    g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, TRUE); //Sätter på ljus
    g_pd3dDevice->SetRenderState(D3DRS_SPECULARENABLE, TRUE); //Sätter på reflektionsljus
    g_pd3dDevice->SetRenderState(D3DRS_AMBIENT, 0xffffffff);

    g_pd3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
    g_pd3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
    g_pd3dDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_ANISOTROPIC);
    g_pd3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSU,  D3DTADDRESS_CLAMP);

    //---------------------------------
    // Synfält
    //---------------------------------
    //Sätter upp Field of View: (matrix, 1/4 PI, Aspect Ratio, synfält start, synfält slut)
    D3DXMATRIX matProj;
    D3DXMatrixPerspectiveFovLH(&matProj, D3DXToRadian(45.0f),
                                4.0f / 3.0f, 0.001f, 500.0f);
    g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);

    return S_OK;
}

//-----------------------------------------------------------------------------
// Frigör objekt från minnet
//-----------------------------------------------------------------------------
void cleanup()
{
    if(g_pd3dDevice != NULL)
        g_pd3dDevice->Release();

    if(g_pD3D != NULL)
        g_pD3D->Release();
}
