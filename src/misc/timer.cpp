#include "timer.h"
#include "..\misc\megazor.h" //Innehåller bra-att-ha funktioner

Timer::Timer()
{
    elapsedTime = 0.0f;
    curTime = 0.0;
    lastTime = 0.0;
}

float Timer::getElapsed() const
{
    return elapsedTime * 0.001;
}

int Timer::getFPS() const
{
    //Medelvärdet av de 1000 senaste FPSvärdena
    int meanFPS = 0;
    for (unsigned int i = 0; i < fps.size(); i++)
        meanFPS += fps[i];

    return meanFPS / fps.size();
}

string Timer::getFPSStr() const
{
    return I2S(getFPS());
}

void Timer::update(double time)
{
    curTime = time;
    elapsedTime = float(curTime - lastTime);
    lastTime = curTime;

    if (fps.size() == 100)
        fps.erase(fps.begin()); //Bara de 100 senaste värdena behålls
    fps.push_back(int(1000.f / elapsedTime)); //Fps = 1000 / tid som renderingen tagit
}
