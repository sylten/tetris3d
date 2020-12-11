#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

#define DEBUG 0

#define FILES_PATH "..\\files\\"
#define WIN_X      300
#define WIN_Y      150
#define WIN_WIDTH  1024
#define WIN_HEIGHT 768

#define PI 3.141592654f

#define BOARD_WIDTH 11
#define BOARD_HEIGHT 21
#define CUBE_LENGTH 1.2f
#define TICK_START 0.3f
#define TICK_DECREASE 0.03f

#define ADD_PATH(str)     ( string(FILES_PATH) + string(str) ) //Lägger till hela sökvägen till files mappen
#define DEGTORAD(degree)  ( (PI / 180.0f) * (degree) )         //Grader till radianer
#define RADTODEG(radian)  ( (180.0f / PI) * (radian) )         //Radianer till grader

#endif
