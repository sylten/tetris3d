#include "tetromino.h"

Tetromino::Tetromino()
{
    x = 0;
    y = 0;
    color = NO_CUBE;
    for (int ix = 0; ix < 4; ix++)
        for (int iy = 0; iy < 4; iy++)
            blocks[ix][iy] = RED;
}

int Tetromino::getCubeId() const
{
    return color;
}
int Tetromino::getBlock(int ix, int iy) const
{
    return blocks[ix][iy];
}

void Tetromino::setPos(int _x, int _y)
{
    x = _x;
    y = _y;
}

void Tetromino::setType(CubeColor c)
{
    x = BOARD_WIDTH + 1;
    y = 1;
    color = c;

    //Återsäll allt till svart
    for (int ix = 0; ix < 4; ix++)
        for (int iy = 0; iy < 4; iy++)
            blocks[ix][iy] = NO_CUBE;

    //Fyll i nya kuber beroende på vilken sort som slumpats fram
    switch(c)
    {
        case CYAN:
        {
            blocks[1][0] = CYAN;
            blocks[1][1] = CYAN;
            blocks[1][2] = CYAN;
            blocks[1][3] = CYAN;
        }break;
        case BLUE:
        {
            blocks[2][1] = BLUE;
            blocks[1][1] = BLUE;
            blocks[1][2] = BLUE;
            blocks[1][3] = BLUE;
        }break;
        case ORANGE:
        {
            blocks[1][1] = ORANGE;
            blocks[2][1] = ORANGE;
            blocks[2][2] = ORANGE;
            blocks[2][3] = ORANGE;
        }break;
        case YELLOW:
        {
            blocks[1][1] = YELLOW;
            blocks[1][2] = YELLOW;
            blocks[2][1] = YELLOW;
            blocks[2][2] = YELLOW;
        }break;
        case GREEN:
        {
            blocks[2][1] = GREEN;
            blocks[1][1] = GREEN;
            blocks[1][2] = GREEN;
            blocks[0][2] = GREEN;
        }break;
        case PURPLE:
        {
            blocks[1][1] = PURPLE;
            blocks[0][2] = PURPLE;
            blocks[1][2] = PURPLE;
            blocks[2][2] = PURPLE;
        }break;
        case RED:
        {
            blocks[0][1] = RED;
            blocks[1][1] = RED;
            blocks[1][2] = RED;
            blocks[2][2] = RED;
        }break;
        case NO_CUBE: break; //För att slippa varningar
    }
}

void Tetromino::cloneType(Tetromino *source)
{
    for (int ix = 0; ix < 4; ix++)
        for (int iy = 0; iy < 4; iy++)
            blocks[ix][iy] = source->getBlock(ix, iy);
}

bool Tetromino::checkCollision(int dx, int dy, int board[BOARD_WIDTH][BOARD_HEIGHT])
{
    int newX = x + dx;
	int newY = y + dy;

    //Kolla om den stött i en kant
	for(int ix = 0; ix < 4; ix++)
		for(int iy = 0; iy < 4; iy++)
			if(blocks[ix][iy] != NO_CUBE &&
              (newX + ix <= 0 || newX + ix >= BOARD_WIDTH ||
               newY + iy >= BOARD_HEIGHT))
                return true;

    //Kolla om den stött i en annan tetromino
	for(int ix = 0; ix < BOARD_WIDTH; ix++)
		for(int iy = 0; iy < BOARD_HEIGHT; iy++)
			if(ix >= newX && ix < newX + 4 &&
              (iy >= newY && iy < newY + 4) &&
              (board[ix][iy] != NO_CUBE) &&
              (blocks[ix - newX][iy - newY] != NO_CUBE))
                return true;

	return false;
}

MoveResult Tetromino::move(int dx, int dy, int board[BOARD_WIDTH][BOARD_HEIGHT])
{
    if(checkCollision(dx, dy, board)) //Kolla om den krockat
	{
		if(dy > 0)
		{
            //Lägg till den här tetrominons block i spelplanen
            for(int ix = 0; ix < 4; ix++)
                for(int iy = 0; iy < 4; iy++)
                    if(blocks[ix][iy] != NO_CUBE)
                        board[x + ix][y + iy] = blocks[ix][iy];

            if(y < 1) //Om den nuddat taket
                return FAIL;
            return NEW;
		}
	}
	else //Om den inte krockat fortsätter den neråt
	{
		x += dx;
		y += dy;
		return NOTHING;
	}
	return NOTHING;
}

void Tetromino::rotate(int board[BOARD_WIDTH][BOARD_HEIGHT])
{
    int temp[4][4];

	//Kopierar och roterar till den temporära matrisen
	for(int ix = 0; ix < 4; ix++)
        for(int iy = 0; iy < 4; iy++)
			temp[3-iy][ix] = blocks[ix][iy];

	//Kollar ifall den temporära krockar med någon kant
	for(int ix = 0; ix < 4; ix++)
		for(int iy = 0; iy < 4; iy++)
			if(temp[ix][iy] != NO_CUBE &&
              (x + ix <= 0 || x + ix >= BOARD_WIDTH ||
               y + iy >= BOARD_HEIGHT))
                return;

	//Kollar ifall den temporära krockar med något block
	for(int ix = 0; ix < BOARD_WIDTH; ix++)
		for(int iy = 0; iy < BOARD_HEIGHT; iy++)
			if(ix >= x && ix < x + 4 &&
              (iy >= y && iy < y + 4) &&
              (board[ix][iy] != NO_CUBE) &&
              (temp[ix - x][iy - y] != NO_CUBE))
                return;

	//Om det lyckades kopieras den temporära matrisen till den riktiga
	for(int ix = 0; ix < 4; ix++)
        for(int iy = 0; iy < 4; iy++)
			blocks[ix][iy] = temp[ix][iy];
}

void Tetromino::render(Model *cube, LPDIRECT3DDEVICE9 d3dDevice)
{
    for (int ix = 0; ix < 4; ix++)
        for (int iy = 0; iy < 4; iy++)
            if (blocks[ix][iy] != NO_CUBE && y + iy > 0)
                cube->render(D3DXVECTOR3((x+ix) * CUBE_LENGTH, (y+iy) * CUBE_LENGTH, 0.0f), d3dDevice);
}

Tetromino::~Tetromino()
{

}
