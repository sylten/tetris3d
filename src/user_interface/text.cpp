#include "text.h"

Text::Text(LPDIRECT3DDEVICE9 d3dDevice)
{
    D3DXCreateFont(d3dDevice, 20, 0, FW_BOLD, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"), &plainSmall);
    D3DXCreateFont(d3dDevice, 20, 0, FW_BOLD, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Century Gothic"), &statsSmall);
    D3DXCreateFont(d3dDevice, 30, 0, FW_BOLD, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Century Gothic"), &statsMedium);
    failX = -150.0f; failY = -150.0f;
}

void Text::show(std::string str, FontType size, int r, int g, int b, int a, int x, int y)
{
    D3DCOLOR fontColor = D3DCOLOR_ARGB(a, r, g, b); //skapa färgen

    //Skapa en rektangel som beskriver var på skärmen texten ska visas, flyttar texten om det är epic fail (när man förlorat spelet)
    RECT rct;
    if (str == "YOU FAIL!")
    {
        rct.left = int(failX);
        rct.top = int(failY);
        failX += 0.1;
        failY += 0.1;
        if (failX > 1024 || failY > 768)
        {
            failX = -150.0f;
            failY = -150.0f;
        }
    }
    else
    {
        rct.left = x;
        rct.top = y;
    }
    rct.right = 1000;
    rct.bottom = rct.top + 1000;

    //Visar texten
    switch(size)
    {
        case PLAIN_SMALL: plainSmall->DrawText(NULL, str.c_str(), -1, &rct, 0, fontColor ); break;
        case STATS_SMALL: statsSmall->DrawText(NULL, str.c_str(), -1, &rct, 0, fontColor ); break;
        case STATS_MEDIUM: statsMedium->DrawText(NULL, str.c_str(), -1, &rct, 0, fontColor ); break;
    }
}

Text::~Text()
{
    plainSmall->Release();
    statsSmall->Release();
    statsMedium->Release();
}
