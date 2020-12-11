#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <d3dx9.h>
#include <vector>
#include <string>
#include "..\misc\camera.h"
#include "..\misc\game_props.h"
#include "..\entities\cube_container.h"
#include "..\entities\player.h"

using namespace std;

class Game
{
	private:
        Camera *cam;
        GameProps *props;
        CubeContainer container;

        vector<Player*> players;

        bool waitForCam;
        bool quit;
        bool paused;
        int textAlpha;
        int fade;

        void renderErr(LPDIRECT3DDEVICE9 d3dDevice);

	public:
		Game(Camera *_cam, GameProps *_props);

        void start();
        bool stop() const;

        void handleInput(KeyboardListener *keyboard);
        void advanceLogic(float elapsedTime);
		void render(string fps, LPDIRECT3DDEVICE9 d3dDevice);

		~Game();
};


#endif // GAME_H_INCLUDED

