// main.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <stdlib.h>

#include "product.h"
#include "branch.h"
#include "menu.h"
using namespace std;

/*               FUNCTIONS               */





/*---------------------------------------*/


int main()
{
    /*Variables*/
    int op;

    /*CODE HERE*/
    do
    {
        system("cls");
        menu();
        cin >> op;
    } while (op != 0);
    return EXIT_SUCCESS;
}

// Ahora si funciona
// Para el mas culon