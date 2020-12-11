#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <d3dx9.h>
#include <string>
#include "tetromino.h"
#include "cube_container.h"
#include "..\misc\game_props.h"
#include "..\input\keyboard_listener.h"

using namespace std;

class Player
{
	private:
        Tetromino current, preview;           //Nuvarande fallande tetromino, preview (nästkommande tetromino)
        int board[BOARD_WIDTH][BOARD_HEIGHT]; //Spelplanen
        CubeContainer *container;

        float tickFull, tickTime; //Tid mellan uppdateringar och tid som väntats sedan senaste uppdatering
        int level;                //Nuvarande level
        int score;                //Nuvarande poäng
        int lines;                //Nuvarande antal lines
        bool failed;              //Om spelaren misslyckats (nått taket)

        DWORD rotateKey, leftKey, rightKey, downKey, useKey; //Knappar

	public:
		Player(CubeContainer *cont);

        string getLevelStr() const;
        string getScoreStr() const;
        string getLinesStr() const;
        bool hasFailed() const;

        void handleInput(KeyboardListener *keyboard);
        void advanceLogic(float elapsedTime);
		void render(int a, GameProps *props, LPDIRECT3DDEVICE9 d3dDevice);

		~Player();
};

#endif // PLAYER_H_INCLUDED
