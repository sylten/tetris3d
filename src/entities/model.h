#ifndef MODEL_H_INCLUDED
#define MODEL_H_INCLUDED

#include <windows.h>
#include <d3dx9.h>
#include <string>

using namespace std;

class Model
{
    private:
        LPD3DXMESH          mesh; //Mesh (modellens grund)
        D3DMATERIAL9*       meshMaterials; //Material...
        LPDIRECT3DTEXTURE9* meshTextures; //Texturer
        DWORD               numMaterials; //Antal material

        D3DXVECTOR3         scale;

        D3DXMATRIX getWorldMatrix(D3DXVECTOR3 pos, D3DXVECTOR3 rot) const;

    public:
        Model();
        Model(string filename, LPDIRECT3DDEVICE9 d3dDevice, float r = -1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f); //Konstruktor, kallar loadModel
        HRESULT loadModel(string filename, LPDIRECT3DDEVICE9 d3dDevice, float r = -1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f); //Laddar in en modell och texturer från filename (-1 == standardfärger från modellfilen)

        void setScale(float sx, float sy, float sz);

        void render(D3DXVECTOR3 pos, D3DXVECTOR3 rot, LPDIRECT3DDEVICE9 d3dDevice) const; //Visa modellen vid x, y, z och med rotationen rot.x radianer runt x-axeln osv
        void render(D3DXVECTOR3 pos, LPDIRECT3DDEVICE9 d3dDevice) const; //Visa modellen vid x, y, z
        ~Model(); //Frigör variabler från minnet
};

float safeRGB(float value);

#endif
