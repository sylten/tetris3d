#include "mouse_listener.h"

MouseListener::MouseListener()
{
    leftClicked = false;
    rightClicked = false;
    middleClicked = false;
}

void MouseListener::update(UINT msg)
{
    switch(msg)
    {
        case WM_LBUTTONDOWN:
			leftClicked = true; break;

		case WM_LBUTTONUP:
			leftClicked = false; break;

        case WM_RBUTTONDOWN:
			rightClicked = true; break;

		case WM_RBUTTONUP:
			rightClicked = false; break;
    }
}

void MouseListener::updatePos(POINT pos)
{
    lastPos = currentPos;
    currentPos = pos;
}
