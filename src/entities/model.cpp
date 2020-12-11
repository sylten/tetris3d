#include "model.h"
#include "..\main\constants.h"

Model::Model()
{
    mesh = NULL;
    meshMaterials = NULL;
    meshTextures = NULL;
    numMaterials = 0L;
    scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

Model::Model(string filename, LPDIRECT3DDEVICE9 d3dDevice, float r, float g, float b, float a)
{
    mesh = NULL;
    meshMaterials = NULL;
    meshTextures = NULL;
    numMaterials = 0L;
    scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

    if (FAILED(loadModel(filename, d3dDevice, r, g, b, a)))
        MessageBox(NULL, string("Failed to load " + filename).c_str(), "Tetris 3D.exe", MB_OK);
}

HRESULT Model::loadModel(string filename, LPDIRECT3DDEVICE9 d3dDevice, float r, float g, float b, float a)
{
    LPD3DXBUFFER pD3DXMtrlBuffer;

    // Load the mesh from the specified file
    if(FAILED(D3DXLoadMeshFromX(filename.c_str(), D3DXMESH_SYSTEMMEM,
                                   d3dDevice, NULL,
                                   &pD3DXMtrlBuffer, NULL, &numMaterials,
                                   &mesh)))
    {
        MessageBox(NULL, string("Could not find " + filename).c_str(), "Tetris 3D.exe", MB_OK);
        return E_FAIL;
    }

    //Tar ut information om material från pD3DXMtrlBuffer
    D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
    meshMaterials = new D3DMATERIAL9[numMaterials];
    if(meshMaterials == NULL)
        return E_OUTOFMEMORY;
    meshTextures = new LPDIRECT3DTEXTURE9[numMaterials];
    if(meshTextures == NULL)
        return E_OUTOFMEMORY;

    for(DWORD i = 0; i < numMaterials; i++)
    {
        meshMaterials[i] = d3dxMaterials[i].MatD3D; //Kopierar materialet

        if (r == -1.0f)
            meshMaterials[i].Ambient = meshMaterials[i].Diffuse; //Sätter ambientfärger
        else
        {
            meshMaterials[i].Diffuse.r = r;
            meshMaterials[i].Diffuse.g = g;
            meshMaterials[i].Diffuse.b = b;
            meshMaterials[i].Diffuse.a = a;

            meshMaterials[i].Ambient.r = r;//safeRGB(r + 0.2);
            meshMaterials[i].Ambient.g = g;//safeRGB(g + 0.2);
            meshMaterials[i].Ambient.b = b;//safeRGB(b + 0.2);
            meshMaterials[i].Ambient.a = a;//safeRGB(a + 0.2);

            /*meshMaterials[i].Specular.r = safeRGB(r + 0.2);
            meshMaterials[i].Specular.g = safeRGB(g + 0.2);
            meshMaterials[i].Specular.b = safeRGB(b + 0.2);
            meshMaterials[i].Specular.a = safeRGB(a + 0.2);*/
        }

        meshTextures[i] = NULL;
        if(d3dxMaterials[i].pTextureFilename != NULL && //Ifall meshens texturfilnamn inte är NULL
            lstrlenA(d3dxMaterials[i].pTextureFilename) > 0) //Och är minst 1 bokstav långt
        {
            string catFilename = FILES_PATH; //Lägger till sökvägen till mappen där texturen ligger
            catFilename.append(d3dxMaterials[i].pTextureFilename);
            //Och laddar in texturen
            if(FAILED(D3DXCreateTextureFromFileA(d3dDevice,
                                                    catFilename.c_str(),
                                                    &meshTextures[i])))
            {
                MessageBox(NULL, string("Could not find " + catFilename).c_str(), "Tetris 3D.exe", MB_OK);
            }
        }
    }

    pD3DXMtrlBuffer->Release();

    return S_OK;
}

void Model::setScale(float sx, float sy, float sz)
{
    scale = D3DXVECTOR3(sx, sy, sz);
}

D3DXMATRIX Model::getWorldMatrix(D3DXVECTOR3 pos, D3DXVECTOR3 rot) const
{
    D3DXMATRIX matTrans;
    D3DXMATRIX matRot;
    D3DXMATRIX matScale;

    D3DXMatrixTranslation(&matTrans, pos.x, pos.y, pos.z); //Placerar renderingen på rätt position
    D3DXMatrixRotationYawPitchRoll(&matRot, rot.x, rot.y, rot.z); //Roterar renderingen till rätt rotation
    D3DXMatrixScaling(&matScale, scale.x, scale.y, scale.z); //Skala

    return matRot * matTrans * matScale;
}

void Model::render(D3DXVECTOR3 pos, D3DXVECTOR3 rot, LPDIRECT3DDEVICE9 d3dDevice) const
{
    D3DXMATRIX matWorld = getWorldMatrix(pos, rot); //Hämtar position/rotation

    d3dDevice->SetTransform(D3DTS_WORLD, &matWorld);

    //Meshs är uppdelade i olika delar för varje material, löper igenom och renderar dem
    for(DWORD i = 0; i < numMaterials; i++)
    {
        //Sätter vilken del som ska renderas
        d3dDevice->SetMaterial(&meshMaterials[i]);
        d3dDevice->SetTexture(0, meshTextures[i]);

        //Rita
        mesh->DrawSubset(i);
    }
}
void Model::render(D3DXVECTOR3 pos, LPDIRECT3DDEVICE9 d3dDevice) const
{
    D3DXMATRIX matWorld = getWorldMatrix(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));

    d3dDevice->SetTransform(D3DTS_WORLD, &matWorld);

    //Meshs är uppdelade i olika delar för varje material, löper igenom och renderar dem
    for(DWORD i = 0; i < numMaterials; i++)
    {
        //Sätter vilken del som ska renderas
        d3dDevice->SetMaterial(&meshMaterials[i]);
        d3dDevice->SetTexture(0, meshTextures[i]);

        //Rita
        mesh->DrawSubset(i);
    }
}

Model::~Model()
{
    if(meshMaterials != NULL)
        delete[] meshMaterials;

    if(meshTextures)
    {
        for(DWORD i = 0; i < numMaterials; i++)
        {
            if(meshTextures[i])
                meshTextures[i]->Release();
        }
        delete[] meshTextures;
    }
    if(mesh != NULL)
        mesh->Release();
}

//-----------------------
// RELATERADE FUNKTIONER
//-----------------------

float safeRGB(float value)
{
    if (value > 1.0f)
        return 1.0f;
    else if (value < 0.0f)
        return 0.0f;

    return value;
}
