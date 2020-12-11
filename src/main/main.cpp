#include "main.h"

//-----------------------------------------------------------------------------
// Initierar Globala variabler
//-----------------------------------------------------------------------------
LPDIRECT3D9          g_pD3D       = NULL;
LPDIRECT3DDEVICE9    g_pd3dDevice = NULL;

KeyboardListener     g_keyboard;
Timer                g_timer;

//-----------------------------------------------------------------------------
// Tar hand om "meddelanden" (Knapptryckningar/musklick etc)
//-----------------------------------------------------------------------------
LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    g_keyboard.update();

    switch(msg)
    {
        case WM_CLOSE:
		{
            cleanup();
            PostQuitMessage(0);
            return 0;
        }

        case WM_DESTROY:
        {
            cleanup();
            PostQuitMessage(0);
            return 0;
        }
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

//-----------------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------------
int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     INT nCmdShow)
{
    //------------------------------------
    // Skapar fönstret
    //------------------------------------

    // Register the window class
    WNDCLASSEX wc =
    {
        sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
        hThisInstance,
        NULL,
        LoadCursor(NULL, IDC_ARROW),
        NULL, NULL,
        "lolwin",
        NULL
    };
    RegisterClassEx(&wc);

    //Skapar fönstret
    HWND hWnd = CreateWindow("lolwin", "Tetris 3D",
                              WS_OVERLAPPEDWINDOW, WIN_X, WIN_Y, WIN_WIDTH, WIN_HEIGHT,
                              NULL, NULL, wc.hInstance, NULL);

    //------------------------------------
    // Initiera Direct3D
    //------------------------------------
    if(SUCCEEDED(initD3D(hWnd)))
    {
        // Visa fönstret
        ShowWindow(hWnd, SW_SHOWDEFAULT);
        UpdateWindow(hWnd);
        //ShowCursor(false);

        MSG msg; //Innehåller meddelanden från tangentbord/mus/etc
        ZeroMemory(&msg, sizeof(msg));

        srand(time(NULL));
        //------------------------------------
        // Initiering av variabler
        //------------------------------------
        Camera cam; //Skapar kameran
        cam.defaultMenuCam(g_pd3dDevice);

        GameProps props(g_pd3dDevice); //Innehåller alla modeller / annat som spelet är uppbyggt av

        Menu menu(&cam, g_pd3dDevice);
        Game game(&cam, &props);
        bool inGame = false;

        //------------------------------------
        // Kör huvudloop
        //------------------------------------

        while(msg.message != WM_QUIT)
        {
            if(PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            else
            {
                //Håller reda på tid
                g_timer.update(timeGetTime());

                if(inGame)
                {
                    game.handleInput(&g_keyboard);
                    game.advanceLogic(g_timer.getElapsed());
                    game.render("FPS: " + g_timer.getFPSStr(), g_pd3dDevice);
                    if (game.stop())
                    {
                        cam.defaultMenuCam(g_pd3dDevice);
                        inGame = false;
                        menu.moveBack();
                    }
                }
                else
                {
                    menu.handleInput(&g_keyboard);
                    menu.render("FPS: " + g_timer.getFPSStr(), &props, g_pd3dDevice);
                    MenuTarget t = menu.checkAction();
                    switch(t)
                    {
                        case START:
                        {
                            cam.defaultGameCam(g_pd3dDevice);
                            game.start();
                            inGame = true;
                        }
                        case HIGHSCORE: break;
                        case OPTIONS: break;
                        case EXIT: cleanup(); PostQuitMessage(0); break;
                        case MAIN: break;
                    }
                }
            }
        }
    }

    UnregisterClass("lolwin", wc.hInstance);
    return 0;
}
