#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include <string>
#include <vector>

using namespace std;

class Timer
{
    private:
        float elapsedTime; //Tid sedan senaste uppdatering
        double curTime; //Tid som g�tt sedan programmet startade
        double lastTime; //Tid som g�tt vid senaste uppdatering

        vector<int> fps; //Inneh�ller fpsen vid de 20 senaste uppdateringarna

    public:
        Timer();

        float getElapsed() const; //Returnerar tid sedan senaste uppdatering
        int getFPS() const; //Returnerar medelv�rdet av FPSen p� de 1000 senaste uppdateringarna
        string getFPSStr() const; //Returnerar medelv�rdet av FPSen som en str�ng

        void update(double time); //Uppdaterar variabler
};

#endif
