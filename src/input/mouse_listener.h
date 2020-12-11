#ifndef MOUSE_LISTENER_H_INCLUDED
#define MOUSE_LISTENER_H_INCLUDED

#include <windows.h>

class MouseListener
{
    public:
        POINT lastPos;
        POINT currentPos;
        bool leftClicked;
        bool rightClicked;
        bool middleClicked;

    public:
        MouseListener();
        void update(UINT msg);
        void updatePos(POINT pos);
};

#endif
