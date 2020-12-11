#include "cube_container.h"

#include <cmath>
#include "..\main\constants.h"
#include "..\misc\megazor.h"

Piece::Piece(CubeColor c, D3DXVECTOR3 _pos, float angle, float ySpeed)
{
    color = c;
    pos = _pos;
    moveVel = D3DXVECTOR3(sin(angle), ySpeed, cos(angle));
    angularVel = D3DXVECTOR3(randNegativity(0.001), randNegativity(0.001), randNegativity(0.001));
    rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

const float CubeContainer::moveSpeed = 0.007f;
const float CubeContainer::gravity = 0.00003f;

CubeContainer::CubeContainer()
{

}

void CubeContainer::add(CubeColor c, D3DXVECTOR3 pos)
{
    if (c != NO_CUBE)
        pieces.push_back(Piece(c, pos, (rand()%628)/100, -0.01));
}

void CubeContainer::advance()
{
    for (unsigned int i = 0; i < pieces.size(); i++)
    {
        pieces[i].pos.x += pieces[i].moveVel.x * moveSpeed;
        pieces[i].pos.y += pieces[i].moveVel.y;
        pieces[i].pos.z += pieces[i].moveVel.z * moveSpeed;

        pieces[i].moveVel.y += gravity;
        pieces[i].rot += pieces[i].angularVel;

        if (pieces[i].pos.y > 33.0f)
            pieces.erase(pieces.begin() + i);
    }
}

void CubeContainer::render(GameProps *props, LPDIRECT3DDEVICE9 d3dDevice)
{
    for (unsigned int i = 0; i < pieces.size(); i++)
        props->cubes[pieces[i].color]->render(pieces[i].pos, pieces[i].rot, d3dDevice);
}

CubeContainer::~CubeContainer()
{
    pieces.clear();
}
