#include "text_3d.h"

Text3D::Text3D(string filename, LPDIRECT3DDEVICE9 d3dDevice)
{
    pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

    HDC hdc;
    HFONT font;

    hdc = CreateCompatibleDC(NULL);

    font = CreateFont(10,         //Height
                      0,          //Width
                      0,          //Escapement
                      0,          //Orientation
                      FW_NORMAL,  //Weight
                      false,      //Italic
                      false,      //Underline
                      false,      //Strikeout
                      DEFAULT_CHARSET,          //Charset
                      OUT_DEFAULT_PRECIS,       //Output Precision
                      CLIP_DEFAULT_PRECIS,      //Clipping Precision
                      DEFAULT_QUALITY,          //Quality
                      DEFAULT_PITCH|FF_DONTCARE,//Pitch and Family
                      "Arial");

    SelectObject(hdc, font);

    D3DXCreateText(d3dDevice,  //Device
                     hdc,             //GDI Device Context
                     filename.c_str(),//Text
                     0.001f,          //Maximum chordal deviation from true font outlines
                     0.4f,            //Extrusion depth (along -Z axis)
                     &mesh,           //Mesh
                     NULL,            //Adjacency information
                     NULL);           //GlyphMetrics
}

D3DXVECTOR3 Text3D::getPos() const
{
    return rot;
}
D3DXVECTOR3 Text3D::getRot() const
{
    return pos;
}

void Text3D::setPos(D3DXVECTOR3 _pos)
{
    pos = _pos;
}
void Text3D::setRot(D3DXVECTOR3 _rot)
{
    rot = _rot;
}

void Text3D::rotate(float elapsedTime)
{
    rot.x += elapsedTime;
}

void Text3D::render(LPDIRECT3DDEVICE9 d3dDevice)
{
    D3DXMATRIX matWorld;
    D3DXMATRIX matTrans;
    D3DXMATRIX matRot;

    D3DXMatrixTranslation(&matTrans, pos.x, pos.y, pos.z); //Placerar renderingen på rätt position
    D3DXMatrixRotationYawPitchRoll(&matRot, rot.x, rot.y, rot.z); //Roterar renderingen till rätt rotation

    matWorld = matTrans * matRot;

    d3dDevice->SetTransform(D3DTS_WORLD, &matWorld);
    mesh->DrawSubset(0);
}

Text3D::~Text3D()
{
    if(mesh)
    {
        mesh->Release();
        mesh=NULL;
    }
}
