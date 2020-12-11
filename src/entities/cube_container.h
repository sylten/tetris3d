#ifndef CUBE_CONTAINER_H_INCLUDED
#define CUBE_CONTAINER_H_INCLUDED

#include <d3dx9.h>
#include <vector>
#include "..\misc\game_props.h"

using namespace std;

struct Piece
{
	CubeColor color;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 moveVel;
	D3DXVECTOR3 angularVel;

	Piece(CubeColor c, D3DXVECTOR3 _pos, float angle, float ySpeed);
};

class CubeContainer
{
	private:
        vector<Piece> pieces;

        static const float moveSpeed;
        static const float gravity;

	public:
		CubeContainer();

		void add(CubeColor c, D3DXVECTOR3 pos);
		void advance();
		void render(GameProps *props, LPDIRECT3DDEVICE9 d3dDevice);

		~CubeContainer();
};


#endif // CUBE_CONTAINER_H_INCLUDED

