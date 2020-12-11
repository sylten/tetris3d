#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

#include <d3dx9.h>
#include <string>

enum FontType
{
    PLAIN_SMALL,
    STATS_SMALL,
    STATS_MEDIUM
};

class Text
{
    private:
        LPD3DXFONT plainSmall;
        LPD3DXFONT statsSmall;
        LPD3DXFONT statsMedium;
        float failX, failY;

    public:
        Text(LPDIRECT3DDEVICE9 d3dDevice);
        void show(std::string str, FontType size, int r, int g, int b, int a, int x, int y); //Visar texten str med färgen rgba vid x, y och med bredden w och höjden h
        ~Text();
};

#endif
