#include "game_props.h"

#include "..\main\constants.h"

GameProps::GameProps(LPDIRECT3DDEVICE9 d3dDevice)
{
    txt = new Text(d3dDevice);

    cubes[CYAN] = new Model(ADD_PATH("cube3.x"), d3dDevice, 0.2f, 0.4f, 0.6f); //Cyan
    cubes[BLUE] = new Model(ADD_PATH("cube3.x"), d3dDevice, 0.0f, 0.2f, 0.6f); //Blå
    cubes[ORANGE] = new Model(ADD_PATH("cube3.x"), d3dDevice, 0.6f, 0.3f, 0.0f); //Orange
    cubes[YELLOW] = new Model(ADD_PATH("cube3.x"), d3dDevice, 0.6f, 0.4f, 0.0f); //Gul
    cubes[GREEN] = new Model(ADD_PATH("cube3.x"), d3dDevice, 0.2f, 0.6f, 0.0f); //Grön
    cubes[PURPLE] = new Model(ADD_PATH("cube3.x"), d3dDevice, 0.3f, 0.0f, 0.6f); //Lila
    cubes[RED] = new Model(ADD_PATH("cube3.x"), d3dDevice, 0.6f, 0.05f, 0.0f); //Röd

    for (int i = 0; i < 7; i++) cubes[i]->setScale(0.2f, 0.2f, 0.2f); //Sätt kubernas skala

    borders[VERTICAL] = new Model(ADD_PATH("cube3.x"), d3dDevice, 0.1f, 0.1f, 0.6f);
    borders[HORIZONTAL] = new Model(ADD_PATH("cube3.x"), d3dDevice, 0.1f, 0.1f, 0.6f);
    borders[VERTICAL]->setScale(0.1f, 5.0f, 0.2f);
    borders[HORIZONTAL]->setScale(2.65f, 0.1f, 0.2f);
}

GameProps::~GameProps()
{
    delete[] cubes;
    delete[] borders;
}
