#include "menu.h"

#include <sstream>
#include "constants.h"
#include "key_names.h"

Menu::Menu(Camera *_cam, LPDIRECT3DDEVICE9 d3dDevice)
{
    cam = _cam;
    mv = MAIN;
    activeItem = START;
    waitForCam = false;

    marker = new Model(ADD_PATH("sphere2.x"), d3dDevice, 0.1f, 0.1f, 0.6f);
    marker->setScale(0.3f, 0.3f, 0.3f);

    links[0].model = new Text3D("Start Game", d3dDevice);
    links[0].model->setPos(D3DXVECTOR3(-0.95f, 6.0f, 0.0f));
    links[0].model->setRot(D3DXVECTOR3(0.0f, -0.20f, 0.0f));
    links[0].leftPos = D3DXVECTOR3(-5.0f, 21.5f, 0.0f);
    links[0].rightPos = D3DXVECTOR3(14.0f, 21.5f, 0.0f);

    links[1].model = new Text3D("High Score", d3dDevice);
    links[1].model->setPos(D3DXVECTOR3(-0.85f, 4.9f, 0.0f));
    links[1].model->setRot(D3DXVECTOR3(0.0f, -0.10f, 0.0f));
    links[1].leftPos = D3DXVECTOR3(-4.0f, 17.5f, 0.0f);
    links[1].rightPos = D3DXVECTOR3(13.3f, 17.5f, 0.0f);

    links[2].model = new Text3D("Options", d3dDevice);
    links[2].model->setPos(D3DXVECTOR3(-0.15f, 3.8f, 0.0f));
    links[2].leftPos = D3DXVECTOR3(-1.5f, 13.6f, 0.0f);
    links[2].rightPos = D3DXVECTOR3(11.0f, 13.6f, 0.0f);

    links[3].model = new Text3D("Exit", d3dDevice);
    links[3].model->setPos(D3DXVECTOR3(0.6f, 2.7f, 0.0f));
    links[3].leftPos = D3DXVECTOR3(1.0f, 10.0f, 0.0f);
    links[3].rightPos = D3DXVECTOR3(8.0f, 10.0f, 0.0f);
}

void Menu::moveBack()
{
    D3DXVECTOR3 cur = cam->getPosition();
    cam->setXYZ(cur.x, cur.y, cur.z + 20.0f);
    cam->moveTo(0.0f, 0.0f, -20.0f, 1000.0f);
}

void Menu::handleInput(KeyboardListener *keyboard)
{
    if (!waitForCam)
    {
        if (keyboard->wasPressed(SE_DOWN))
            if (activeItem == EXIT)
                activeItem = START;
            else
                activeItem++;

        if (keyboard->wasPressed(SE_UP))
            if (activeItem == START)
                activeItem = EXIT;
            else
                activeItem--;

        if (keyboard->wasPressed(SE_RETURN))
        {
            switch(activeItem)
            {
                case START: cam->moveTo(0.0f, 4.5f, 20.0f, 1000.0f); break;
                case HIGHSCORE: break;
                case OPTIONS: break;
                case EXIT: break;
                default: break;
            }
            waitForCam = true;
        }
    }
}

MenuTarget Menu::checkAction()
{
    if(waitForCam && !cam->isMoving())
    {
        waitForCam = false;
        return MenuTarget(activeItem);
    }
    return MAIN;
}

void Menu::render(string fps, GameProps *props, LPDIRECT3DDEVICE9 d3dDevice)
{
    d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
                     D3DCOLOR_XRGB(0, 0, 35), 1.0f, 0);

    cam->updateView(d3dDevice);
    if(SUCCEEDED(d3dDevice->BeginScene()))
    {
        if (mv == MAIN)
        {
            marker->render(links[activeItem].leftPos, d3dDevice);
            marker->render(links[activeItem].rightPos, d3dDevice);
            for(int i = 0; i < 4; i++)
                links[i].model->render(d3dDevice);
        }

        props->txt->show(fps, PLAIN_SMALL, 255, 204, 0, 255, 5, 5);
        renderErr(props, d3dDevice);

        d3dDevice->EndScene();
    }
    d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void Menu::renderErr(GameProps *props, LPDIRECT3DDEVICE9 d3dDevice)
{
    D3DXVECTOR3 v = cam->getPosition();
    D3DXVECTOR3 v2 = cam->getTargetPos();
    stringstream ss;
    ss << "pos: (" << v.x << ", " << v.y << ", " << v.z <<") tar: (" << v2.x << ", " << v2.y << ", " << v2.z << ")";
    stringstream ss2;
    ss2 << "waitForCam:" << waitForCam << " cam moving:" << cam->isMoving();
    props->txt->show(ss.str(), PLAIN_SMALL, 255, 204, 0, 255, 200, 5);
    props->txt->show(ss2.str(), PLAIN_SMALL, 255, 204, 0, 255, 200, 30);
}

Menu::~Menu()
{
    delete cam;
    delete[] links;
}
