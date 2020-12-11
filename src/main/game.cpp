#include "game.h"

#include <sstream>
#include "constants.h"
#include "key_names.h"
#include "..\misc\error.h"

Game::Game(Camera *_cam, GameProps *_props)
{
    cam = _cam;
    props = _props;
    players.push_back(new Player(&container));
}

void Game::start()
{
    waitForCam = true;
    paused = false;
    quit = false;
    textAlpha = 0;
    fade = 1;
    cam->setXYZ(1.33f, 2.4f, 0.0f);
    cam->moveTo(0.0f, 0.0f, 8.0f, 1000.0f);
}

bool Game::stop() const
{
    return quit;
}

void Game::handleInput(KeyboardListener *keyboard)
{
    if (!waitForCam)
    {
        for (unsigned int i = 0; i < players.size(); i++)
            players[i]->handleInput(keyboard);

        if (keyboard->wasPressed(SE_ESCAPE))
            if (paused) paused = false;
            else paused = true;
    }
    if (players[0]->hasFailed() && keyboard->wasPressed(SE_RETURN))
        quit = true;
}

void Game::advanceLogic(float elapsedTime)
{
    if (!paused)
    {
        textAlpha += fade;
        if (textAlpha < 0)
            textAlpha = 0;
        else if (textAlpha > 2550)
            textAlpha = 2550;

        if (players[0]->hasFailed() && !waitForCam)
        {
            cam->moveTo(0.0f, 0.0f, -8.0f, 3000.0f);
            fade = -1;
            waitForCam = true;
        }
        else if (waitForCam && !cam->isMoving())
            waitForCam = false;

        if (!waitForCam && !quit)
        {
            for (unsigned int i = 0; i < players.size(); i++)
                players[i]->advanceLogic(elapsedTime);

            container.advance();
        }
    }
}

void Game::render(string fps, LPDIRECT3DDEVICE9 d3dDevice)
{
    //Rensa skärmen
    d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
                         D3DCOLOR_XRGB(0, 0, 35), 1.0f, 0);

    cam->updateView(d3dDevice);

    //Börja rendera vad som visas
    if(SUCCEEDED(d3dDevice->BeginScene()))
    {
        for (unsigned int i = 0; i < players.size(); i++)
            players[i]->render(textAlpha/10, props, d3dDevice);

        container.render(props, d3dDevice);
        props->txt->show(fps, PLAIN_SMALL, 255, 204, 0, 255, 5, 5);
        if (paused) props->txt->show("PAUSED", STATS_SMALL, 255, 204, 0, 255, 475, 300);

        if (DEBUG) renderErr(d3dDevice);

        d3dDevice->EndScene();
    }

    //Visa det som renderats
    d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void Game::renderErr(LPDIRECT3DDEVICE9 d3dDevice)
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

Game::~Game()
{
    delete cam;
    delete props;
    players.clear();
}
