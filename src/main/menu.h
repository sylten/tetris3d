#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <d3dx9.h>
#include "..\misc\camera.h"
#include "..\misc\game_props.h"
#include "..\input\keyboard_listener.h"
#include "..\user_interface\text_3d.h"

enum MenuTarget
{
    MAIN = -1,
    START = 0,
    HIGHSCORE = 1,
    OPTIONS = 2,
    EXIT = 3
};

struct MenuItem
{
    Text3D *model;
    D3DXVECTOR3 leftPos;
    D3DXVECTOR3 rightPos;
};

class Menu
{
	private:
        Camera *cam;
        Model *marker;
        MenuItem links[4];

        MenuTarget mv;
        int activeItem;
        bool waitForCam;

        void renderErr(GameProps *props, LPDIRECT3DDEVICE9 d3dDevice);
	public:
		Menu(Camera *_cam, LPDIRECT3DDEVICE9 d3dDevice);

        void moveBack();

        void handleInput(KeyboardListener *keyboard);
        MenuTarget checkAction();
		void render(string fps, GameProps *props, LPDIRECT3DDEVICE9 d3dDevice);

		~Menu();
};


#endif // MENU_H_INCLUDED

