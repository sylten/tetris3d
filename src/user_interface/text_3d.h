#ifndef TEXT_3D_H_INCLUDED
#define TEXT_3D_H_INCLUDED

#include <d3dx9.h>
#include <string>

using namespace std;

class Text3D
{
	private:
        LPD3DXMESH mesh;
        D3DXVECTOR3 pos;
        D3DXVECTOR3 rot;

	public:
		Text3D(string text, LPDIRECT3DDEVICE9 d3dDevice);

        D3DXVECTOR3 getPos() const;
        D3DXVECTOR3 getRot() const;

		void setPos(D3DXVECTOR3 _pos);
		void setRot(D3DXVECTOR3 _rot);

        void rotate(float elapsedTime);

		void render(LPDIRECT3DDEVICE9 d3dDevice);
		~Text3D();
};


#endif // TEXT_3D_H_INCLUDED

