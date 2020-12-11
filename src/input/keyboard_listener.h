#ifndef KEYBOARD_LISTENER_H_INCLUDED
#define KEYBOARD_LISTENER_H_INCLUDED

#include <windows.h>

class KeyboardListener
{
    private:
        unsigned char keys[256];
        bool frozen[256];

    public:
        KeyboardListener();

        bool isPressed(DWORD keyId); //Returnerar om keyId �r nedtryckt
        bool wasPressed(DWORD keyId); //Returnerar om keyId �r nedtryckt men knappen m�ste ha lyfts innan den returnerar true igen

        bool isFrozen(DWORD keyId) const;
        void freeze(DWORD keyId);
        void unfreeze(DWORD keyId);

        void update();
};

#endif
