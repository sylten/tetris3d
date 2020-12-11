#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include <string>
#include <vector>

using namespace std;

class Timer
{
    private:
        float elapsedTime; //Tid sedan senaste uppdatering
        double curTime; //Tid som gått sedan programmet startade
        double lastTime; //Tid som gått vid senaste uppdatering

        vector<int> fps; //Innehåller fpsen vid de 20 senaste uppdateringarna

    public:
        Timer();

        float getElapsed() const; //Returnerar tid sedan senaste uppdatering
        int getFPS() const; //Returnerar medelvärdet av FPSen på de 1000 senaste uppdateringarna
        string getFPSStr() const; //Returnerar medelvärdet av FPSen som en sträng

        void update(double time); //Uppdaterar variabler
};

#endif
