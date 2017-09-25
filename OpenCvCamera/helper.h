#ifndef HELPER_H
#define HELPER_H

#include <cstdlib>
#include <ctime>

int random(int from , int to){

    // generates random number between them from and to
    srand(time(nullptr));

    return (rand() % to) + from;

}

#endif
