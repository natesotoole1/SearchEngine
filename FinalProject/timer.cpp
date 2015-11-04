#include "timer.h"

Timer::Timer()
{

}

Timer::Timer(string theName) : name(theName), start(clock())
{

}


Timer::~Timer()
{
    end = clock();

    float timeElapsed = ((float)end - (float)start) / CLOCKS_PER_SEC;
    cout<<endl<<name<<" took "<<timeElapsed<<"seconds."<<endl;

}
