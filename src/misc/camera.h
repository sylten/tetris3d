#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include <d3dx9.h>

class Camera
{
    public:
        D3DXVECTOR3 eyePt; //Kamerans position
        D3DXVECTOR3 lookPt; //Position dit kameran tittar
        D3DXVECTOR3 upVec; //Håller reda på vilket håll som är upp
        D3DXVECTOR3	rightVec; //Håller reda på vilket håll som är höger

        D3DXVECTOR3 pos;
        D3DXVECTOR3 vel;
        bool move;

        D3DXVECTOR3 direction; //Rotation

        D3DLIGHT9 sunLight;

    public:
        Camera();
        void updateView(LPDIRECT3DDEVICE9 d3dDevice); //"visar" kameran

        void defaultGameCam(LPDIRECT3DDEVICE9 d3dDevice);
        void defaultMenuCam(LPDIRECT3DDEVICE9 d3dDevice);

        void moveTo(float x, float y, float z, float speed);

        void setXYZ(float x, float y, float z);
        void addXYZ(float x, float y, float z);
        void setDirXYZ(float x, float y, float z);
        void addDirXYZ(float x, float y, float z);

        bool isMoving() const;

        D3DXVECTOR3 getPosition() const;
        D3DXVECTOR3 getTargetPos() const;
        D3DXVECTOR3 getRotation() const;
};

#endif
