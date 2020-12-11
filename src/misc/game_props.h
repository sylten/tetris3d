#ifndef GAME_PROPS_H_INCLUDED
#define GAME_PROPS_H_INCLUDED

#include "..\entities\model.h"
#include "..\user_interface\text.h"

enum CubeColor
{
    NO_CUBE = -1,
    CYAN = 0,
    BLUE = 1,
    ORANGE = 2,
    YELLOW = 3,
    GREEN = 4,
    PURPLE = 5,
    RED = 6,
};

enum Orientation
{
    HORIZONTAL = 0,
    VERTICAL = 1
};

class GameProps
{
	public:
        Model* cubes[7]; //De 7 olika färgade kuberna som bygger upp alla tetrominos
        Model* borders[2]; //Två kantbitar som används till ramen
        Text* txt; //Används till att skriva texter

		GameProps(LPDIRECT3DDEVICE9 d3dDevice);
		~GameProps();
};


#endif // GAME_PROPS_H_INCLUDED

