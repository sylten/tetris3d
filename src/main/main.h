#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <windows.h>                    //Skapa fönster mm
#include <windowsx.h>                   //Diverse funktioner
#include <mmsystem.h>                   //Tidtagning
#include <d3dx9.h>                      //Direct3D (Grafik)
#include <vector>
#include <string>
#include "constants.h"                  //Konstanter och andra defines
#include "key_names.h"                  //Namn på alla olika tangentbordets knappar
#include "game.h"
#include "menu.h"
#include "..\entities\player.h"
#include "..\entities\cube_container.h"
#include "..\resources\resource.h"      //För ikonen till .exe filen
#include "..\input\mouse_listener.h"    //Tar upp musklick
#include "..\input\keyboard_listener.h" //Tar upp tangentbordstryck
#include "..\misc\camera.h"
#include "..\misc\timer.h"
#include "..\misc\game_props.h"
#include "..\misc\megazor.h"
#include "..\user_interface\text.h"     //Används för att skriva text på skärmen
#include "..\user_interface\text_3d.h"   //En 3Dtext

using namespace std;

//Globala variabler
extern LPDIRECT3D9       g_pD3D;
extern LPDIRECT3DDEVICE9 g_pd3dDevice;

extern KeyboardListener  g_keyboard;
extern Timer             g_timer;

//init_clean.cpp
HRESULT initD3D(HWND hWnd); //Initierar Direct3D och sätter upp ett "huvud"ljus
void    cleanup(); //Frigör DirectX variabler från minnet

//input_handling.cpp
LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam); //Meddelandeloopen tar hand om alla meddelanden från fönstret (knapptryck/musklick/etc)

//main.cpp
int     WINAPI WinMain (HINSTANCE hThisInstance, //Main, skapar fönstret och innehåller mainloop
                        HINSTANCE hPrevInstance,
                        LPSTR lpszArgument,
                        INT nCmdShow);

#endif // MAIN_H_INCLUDED
