#include "Rand.h"
#include <ctime>
#include <random>
//Mis en place du compteur
int Rand::cnt = 0;

//Vérification du compteur
void Rand::checkSeed()
{
    //Si on a trop appelé le générateur de nombres, on remet le tout à zéro
    if ((!cnt) || (cnt > 10))
    {
        srand(time(NULL));
        cnt = 0;
    }
}

//Générer une nouvelle séquence...
void Rand::newSeed(int s)
{
    srand(s);
}

//Générer un nombre aléatoire
int Rand::randi()
{
    checkSeed();
    return rand();
}

//Générer un nombre aléatoire entre [0,max-1]
int Rand::randi(int max)
{
    checkSeed();
    if (max)
        return rand() % max;
    return 0;
}