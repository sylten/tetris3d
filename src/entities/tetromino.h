#ifndef TETROMINO_H_INCLUDED
#define TETROMINO_H_INCLUDED

#include "model.h"
#include "..\main\constants.h"
#include "..\misc\game_props.h"

enum MoveResult
{
    FAIL,
    NEW,
    NOTHING
};

class Tetromino
{
	private:
		int blocks[4][4];
		int x, y;
		CubeColor color;

		bool checkCollision(int dx, int dy, int board[BOARD_WIDTH][BOARD_HEIGHT]);

	public:
		Tetromino();

        int getCubeId() const;
        int getBlock(int ix, int iy) const;

        void setPos(int _x, int _y);

        void setType(CubeColor c); //Sätter upp block beroende på c
        void cloneType(Tetromino *source); //Kopierar block ifrån source

		MoveResult move(int dx, int dy, int board[BOARD_WIDTH][BOARD_HEIGHT]);
		void rotate(int board[BOARD_WIDTH][BOARD_HEIGHT]);

		void render(Model *cube, LPDIRECT3DDEVICE9 d3dDevice);

		~Tetromino();
};


#endif // TETROMINO_H_INCLUDED

