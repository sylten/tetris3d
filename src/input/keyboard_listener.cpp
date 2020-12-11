#include "keyboard_listener.h"

KeyboardListener::KeyboardListener()
{
    for (int i = 0; i < 256; i++)
        frozen[i] = false;
}

bool KeyboardListener::isPressed(DWORD keyId)
{
    return (keys[keyId] & 0x80);
}

bool KeyboardListener::wasPressed(DWORD keyId)
{
    if (keys[keyId] & 0x80 && !frozen[keyId])
    {
        frozen[keyId] = true;
        return true;
    }
    else if (!(keys[keyId] & 0x80))
        frozen[keyId] = false;
    return false;
}

bool KeyboardListener::isFrozen(DWORD keyId) const
{
    return frozen[keyId];
}

void KeyboardListener::freeze(DWORD keyId)
{
    frozen[keyId] = true;
}

void KeyboardListener::unfreeze(DWORD keyId)
{
    frozen[keyId] = false;
}

void KeyboardListener::update()
{
    GetKeyboardState(keys);
}
