#include "megazor.h"
#include "..\main\constants.h"
#include <fstream>

SE_Color::SE_Color(int _r, int _g, int _b, int _a)
{
    r = _r; g = _g; b = _b; a = _a;
}
D3DXCOLOR SE_Color::toD3D() const
{
    return D3DCOLOR_ARGB(r, g, b, a);
}
D3DXCOLOR SE_Color::toD3DX() const
{
    return D3DCOLOR_XRGB(r, g, b);
}

//RANDOM FUNKTIONER
SE_Color getLevelColor(int lv)
{
    switch(lv)
    {
        case 1: return SE_Color(30, 60, 30, 255);
        case 2: return SE_Color(30, 60, 30, 255);
        case 3: return SE_Color(30, 60, 30, 255);
        case 4: return SE_Color(30, 60, 30, 255);
        case 5: return SE_Color(30, 60, 30, 255);
        case 6: return SE_Color(30, 60, 30, 255);
        case 7: return SE_Color(30, 60, 30, 255);
        case 8: return SE_Color(30, 60, 30, 255);
        case 9: return SE_Color(30, 60, 30, 255);
        default: return SE_Color(30, 60, 30, 255);
    }
}

void print(string s)
{
    ofstream wFile("error.txt", ios_base::app);
    wFile << s << endl;
    wFile.close();
}
float randNegativity(float val)
{
    if (rand()%10 > 5)
        return val;
    return -val;
}

//KONVERTERING

string I2S(int nr, int base)
{
    char buffer[11];
    itoa(nr, buffer, base);
    return string(buffer);
};

string D2S(double d)
{
    ostringstream ss;
    ss << d;
    return ss.str();
};

wstring S2WS(const string& s)
{
	int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}

//STRÄNGFUNKTIONER

string replaceStr(string text, string replaceWhat, string replaceWith)
{
    if (text.find(replaceWhat) == string::npos)
        return "STRING_NOT_FOUND";

    return text.replace(text.find(replaceWhat), replaceWhat.length(), replaceWith);
};

string getSubstr(string text, string startString, string endString)
{
    string reader = text;
    unsigned int start = reader.find(startString, 0);
    unsigned int end = reader.find(endString,start);
    reader = reader.substr(start+startString.size(),end-(start+startString.size()));
    if (start == string::npos || end == string::npos)
        return "NO_STRING_FOUND";
    else
        return reader;
};

string getSubstr(string text, int startPos, int endPos)
{
    string reader = text;
    reader = reader.substr(startPos, endPos);
    return reader;
};

string stripSpaces(string text)
{
    bool skip = false;
    for (unsigned int i = 0; i < text.length(); i++)
    {
        if (text[i] == '\"')
        {
            if (skip)
                skip = false;
            else
                skip = true;
            text.erase(i,1);
            i--;
        }
        else if (text[i] == ' ' && !skip)
        {
            text.erase(i,1);
            i--;
        }
    }
    return text;
};
