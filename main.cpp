#include "userInterface.h"

#ifdef _TEST
#include <iostream>
#else
#include <ctime>        //for time()
#include <cstdlib>      //for srand and rand
#endif // _TEST

int main()
{
    UserInterface uI;

    #ifdef _TEST
    int errors;
    errors = uI.test();
    ( errors ) ? std::cout << "Ilosc bledow: " << errors : std::cout << "Brak bledow :-)";
    #else
    srand( time( NULL ) );

    system( "clear || cls" );
    int a;
    do{
        a = uI.chooseAction();
        if( a == 7 )
            break;
        uI.executeAction( a );
    }while( a != 7 );
    #endif // _TEST

    return 0;
}
