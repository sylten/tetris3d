#ifndef MEGAZOR_H
#define MEGAZOR_H

#include <windows.h>
#include <d3dx9.h>
#include <string>
#include <sstream>

using namespace std;

struct SE_Color
{
    int r,g,b,a;

    SE_Color(int _r, int _g, int _b, int _a);
    D3DXCOLOR toD3D() const;
    D3DXCOLOR toD3DX() const;
};

//RANDOM FUNKTIONER
SE_Color getLevelColor(int lv);
void print(string s);
float randNegativity(float val);

//KONVERTERING
string  I2S (int nr, int base = 10); //Konvertera en int till string med decimalsystemet base (default 10)
string  D2S (double d); //Konvertera en double till en string
wstring S2WS(const string& s); //Konvertera en string till en wstring

//STRÄNGFUNKTIONER
string replaceStr (string text, string replaceWhat, string replaceWith); //returnerar en kopia av text där replaceWhat är utbyten mot replaceWith i strängen text
string getSubstr  (string text, string startString, string endString); //få stringen mellan startString och endString i text, om inte startString eller endString hittas returneras "NO_STRING_FOUND"
string getSubstr  (string text, int startPos, int endPos); //få strängen mellan startPos och till och med endPos
string stripSpaces(string text); //returnerar en kopia av text utan mellanslag, text inom "" behåller mellanslag och " tas bort

#endif
