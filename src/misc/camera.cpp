#include "camera.h"

#include <mmsystem.h>
#include <cmath>
#include "..\main\constants.h"

Camera::Camera()
{
    eyePt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    lookPt = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
    upVec = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    rightVec = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

    direction = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

    move = false;
}

void Camera::updateView(LPDIRECT3DDEVICE9 d3dDevice)
{
    if (move)
    {
        bool done = true;
        if (eyePt.x > pos.x + vel.x || eyePt.x < pos.x - vel.x)
        {
            eyePt.x += vel.x;
            done = false;
        }
        if (eyePt.y > pos.y + vel.y || eyePt.y < pos.y - vel.y)
        {
            eyePt.y += vel.y;
            done = false;
        }
        if (eyePt.z > pos.z + vel.z || eyePt.z < pos.z - vel.z)
        {
            eyePt.z += vel.z;
            done = false;
        }
        if (done)
        {
            eyePt = pos;
            move = false;
        }
    }

    //Rotation
    upVec = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    lookPt = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
    rightVec = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

    D3DXMATRIX matRotation;
    if(direction.y != 0) //Rotation runt y
    {
        D3DXMatrixRotationAxis(&matRotation, &rightVec, direction.y);
        D3DXVec3TransformCoord(&lookPt, &lookPt, &matRotation);
        D3DXVec3TransformCoord(&upVec, &upVec, &matRotation);
    }

    if(direction.x != 0) //Rotation runt x
    {
        D3DXMatrixRotationAxis(&matRotation, &upVec, direction.x);
        D3DXVec3TransformCoord(&lookPt, &lookPt, &matRotation);
        D3DXVec3TransformCoord(&upVec, &upVec, &matRotation);
    }

    //Synfält
    D3DXMATRIX view;
	D3DXMatrixIdentity(&view);

	D3DXVec3Normalize(&lookPt, &lookPt);
	D3DXVec3Cross(&rightVec, &upVec, &lookPt);
	D3DXVec3Normalize(&rightVec, &rightVec);
	D3DXVec3Cross(&upVec, &lookPt, &rightVec);
	D3DXVec3Normalize(&upVec, &upVec);

	view._11 = rightVec.x;
    view._12 = upVec.x;
    view._13 = lookPt.x;
	view._14 = 0.0f;

	view._21 = rightVec.y;
    view._22 = upVec.y;
    view._23 = lookPt.y;
	view._24 = 0.0f;

	view._31 = rightVec.z;
    view._32 = upVec.z;
    view._33 = lookPt.z;
	view._34 = 0.0f;

	view._41 = -D3DXVec3Dot(&eyePt, &rightVec);
	view._42 = -D3DXVec3Dot(&eyePt, &upVec);
	view._43 = -D3DXVec3Dot(&eyePt, &lookPt);
	view._44 =  1.0f;

	d3dDevice->SetTransform(D3DTS_VIEW, &view);
}

void Camera::defaultGameCam(LPDIRECT3DDEVICE9 d3dDevice)
{
    move = false;

    eyePt = D3DXVECTOR3(1.33f, 2.4f, 8.0f);
    direction = D3DXVECTOR3(0.0f, PI, 0.0f);

    ZeroMemory(&sunLight, sizeof(D3DLIGHT9));
    sunLight.Type       = D3DLIGHT_DIRECTIONAL;
    sunLight.Diffuse.r  = 0.3f;
    sunLight.Diffuse.g  = 0.3f;
    sunLight.Diffuse.b  = 0.3f;
    sunLight.Diffuse.a  = 1.0f;
    sunLight.Range      = 1000.0f;

    D3DXVECTOR3 vecDir = D3DXVECTOR3(0.0f, -0.3f, -0.5);
    D3DXVec3Normalize((D3DXVECTOR3*)&sunLight.Direction, &vecDir);

    d3dDevice->SetLight(0, &sunLight);
    d3dDevice->LightEnable(0, TRUE);
}

void Camera::defaultMenuCam(LPDIRECT3DDEVICE9 d3dDevice)
{
    move = false;

    eyePt = D3DXVECTOR3(1.33f, 2.4f, -18.0f);
    direction = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

    ZeroMemory(&sunLight, sizeof(D3DLIGHT9));
    sunLight.Type       = D3DLIGHT_DIRECTIONAL;
    sunLight.Diffuse.r  = 0.8f;
    sunLight.Diffuse.g  = 0.8f;
    sunLight.Diffuse.b  = 0.8f;
    sunLight.Diffuse.a  = 1.0f;
    sunLight.Range      = 1000.0f;

    D3DXVECTOR3 vecDir = D3DXVECTOR3(0.0f, 0.3f, 0.5);
    D3DXVec3Normalize((D3DXVECTOR3*)&sunLight.Direction, &vecDir);

    d3dDevice->SetLight(0, &sunLight);
    d3dDevice->LightEnable(0, TRUE);
}

void Camera::moveTo(float x, float y, float z, float speed)
{
    move = true;
    pos = D3DXVECTOR3(eyePt.x + x, eyePt.y + y, eyePt.z + z);
    vel.x = (pos.x - eyePt.x) / (speed);
    vel.y = (pos.y - eyePt.y) / (speed);
    vel.z = (pos.z - eyePt.z) / (speed);
}

void Camera::setXYZ(float x, float y, float z)
{
    eyePt.x = x;
    eyePt.y = y;
    eyePt.z = z;
}

void Camera::addXYZ(float x, float y, float z)
{
    eyePt.x += x;
    eyePt.y += y;
    eyePt.z += z;
}

void Camera::setDirXYZ(float x, float y, float z)
{
    direction.x = x;
    direction.y = y;
    direction.z = z;
}

void Camera::addDirXYZ(float x, float y, float z)
{
    direction.x += x;
    direction.y += y;
    direction.z += z;
}

bool Camera::isMoving() const
{
    return move;
}

D3DXVECTOR3 Camera::getPosition() const
{
    return eyePt;
}

D3DXVECTOR3 Camera::getTargetPos() const
{
    return pos;
}

D3DXVECTOR3 Camera::getRotation() const
{
    return direction;
}
