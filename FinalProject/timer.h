#ifndef TIMER_H
#define TIMER_H

#include <time.h>
#include <iostream>

using namespace std;
/*! \brief
 *checks for the function time of each function when called
 */
class Timer
{
public:
    Timer();///< constructor
    Timer(string theName); ///< overloaded constructor
    ~Timer();///< destructor
private:
    string name;

    clock_t start, end;///< called for start and time of the clock

};

#endif // TIMER_H
