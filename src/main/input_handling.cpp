#include "main.h"

//-----------------------------------------------------------------------------
// Tar hand om "meddelanden" (Knapptryckningar/musklick etc)
//-----------------------------------------------------------------------------
LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    g_keyboard.update();

    switch(msg)
    {
        case WM_CLOSE:
			PostQuitMessage(0);	break;

        case WM_DESTROY:
        {
            cleanup();
            PostQuitMessage(0);
            return 0;
        }
        case WM_KEYDOWN:
        {
            if (wParam == VK_ESCAPE)
            {
                cleanup();
                PostQuitMessage(0);
                return 0;
            }
        }
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}
