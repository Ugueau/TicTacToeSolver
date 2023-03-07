#include "Rand.h"
#include <ctime>
#include <random>
//Mis en place du compteur
int Rand::cnt = 0;

//V�rification du compteur
void Rand::checkSeed()
{
    //Si on a trop appel� le g�n�rateur de nombres, on remet le tout � z�ro
    if ((!cnt) || (cnt > 10))
    {
        srand(time(NULL));
        cnt = 0;
    }
}

//G�n�rer une nouvelle s�quence...
void Rand::newSeed(int s)
{
    srand(s);
}

//G�n�rer un nombre al�atoire
int Rand::randi()
{
    checkSeed();
    return rand();
}

//G�n�rer un nombre al�atoire entre [0,max-1]
int Rand::randi(int max)
{
    checkSeed();
    if (max)
        return rand() % max;
    return 0;
}