#include <iostream>
#include <cstdlib>

#include "resourceManager.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#define Sleep(x) usleep((x)*1000)
#endif

#define FACTOR 7

ResourceManager::ResourceManager()
{
    m_tour = 1;
    m_resources[ 0 ] = Resource( "Z\210oto", 10 );       //0
    m_resources[ 1 ] = Resource( "Stal", 50 );           //1
    m_resources[ 2 ] = Resource( "Drewno", 300 );        //2
    m_resources[ 3 ] = Resource( "Kamie\344", 100 );     //3
    m_resources[ 4 ] = Resource( "Zwierz\251ta", 60 );   //4

    m_resources[ 5 ] = Resource( "G\242rnicy", 0 );      //5
    m_resources[ 6 ] = Resource( "Stalownicy", 0 );      //6
    m_resources[ 7 ] = Resource( "Drwale", 0 );          //7
    m_resources[ 8 ] = Resource( "Kamieniarze", 0 );     //8
    m_resources[ 9 ] = Resource( "Farmerzy", 0 );        //9

    m_resources[ 10 ] = Resource( "Kopalnie", 0 );        //10
    m_resources[ 11 ] = Resource( "Huty stali", 1 );      //11
    m_resources[ 12 ] = Resource( "Tartak", 1 );          //12
    m_resources[ 13 ] = Resource( "Kamienio\210omy", 1 ); //13
    m_resources[ 14 ] = Resource( "Farmy", 0 );            //14
}

void ResourceManager::nextTurn()
{
    resourcesAssign();
    endMutiny();
    mutiny();
    hungry();
    if( rand()%6 == 1 ) breakdown();
    if( rand()%8 == 1 ) thiefs();
    if( rand()%10 == 1 ) miracle();
    if( rand()%20 == 1 ) destruction();

    m_tour++;
}

//NOWA TURA
void ResourceManager::resourcesAssign()
{
    if( m_resources[ 10 ].getQuantity() )
        m_resources[ 0 ].addResources( ( m_resources[ 5 ].getQuantity() - m_resources[ 5 ].getMutiny() - ( ( m_resources[ 5 ].getQuantity() - m_resources[ 5 ].getMutiny() ) / m_resources[ 10 ].getQuantity() ) * m_resources[ 10 ].getMutiny() ) * 3 * ( m_tour / FACTOR + 1 ) );
    if( m_resources[ 11 ].getQuantity() )
        m_resources[ 1 ].addResources( ( m_resources[ 6 ].getQuantity() - m_resources[ 6 ].getMutiny() - ( ( m_resources[ 6 ].getQuantity() - m_resources[ 6 ].getMutiny() ) / m_resources[ 11 ].getQuantity() ) * m_resources[ 11 ].getMutiny() ) * 15 );
    if( m_resources[ 12 ].getQuantity() )
        m_resources[ 2 ].addResources( ( m_resources[ 7 ].getQuantity() - m_resources[ 7 ].getMutiny() - ( ( m_resources[ 7 ].getQuantity() - m_resources[ 7 ].getMutiny() ) / m_resources[ 12 ].getQuantity() ) * m_resources[ 12 ].getMutiny() ) * 50 );
    if( m_resources[ 13 ].getQuantity() )
        m_resources[ 3 ].addResources( ( m_resources[ 8 ].getQuantity() - m_resources[ 8 ].getMutiny() - ( ( m_resources[ 8 ].getQuantity() - m_resources[ 8 ].getMutiny() ) / m_resources[ 13 ].getQuantity() ) * m_resources[ 13 ].getMutiny() ) * 30 );
    if( m_resources[ 14 ].getQuantity() )
        m_resources[ 4 ].addResources( ( m_resources[ 9 ].getQuantity() - m_resources[ 9 ].getMutiny() - ( ( m_resources[ 9 ].getQuantity() - m_resources[ 9 ].getMutiny() ) / m_resources[ 14 ].getQuantity() ) * m_resources[ 14 ].getMutiny() ) * 6 * ( m_tour / FACTOR + 1 ) );
}

void ResourceManager::mutiny()
{
    int hungryWorkers = 0;
    int workers = m_resources[ 5 ].getQuantity() + m_resources[ 6 ].getQuantity() + m_resources[ 7 ].getQuantity() + m_resources[ 8 ].getQuantity() + m_resources[ 9 ].getQuantity();

    //Robotnicy, ktorzy nie dostali zlota rozpoczynaj\245 strajk
    if( workers <= m_resources[ 0 ].getQuantity() / ( m_tour / FACTOR + 1 ) )
        m_resources[ 0 ].substractResources( workers * ( m_tour / FACTOR + 1 ));
    else{
        hungryWorkers = workers - m_resources[ 0 ].getQuantity() / ( m_tour / FACTOR + 1 );
        for( int i = 0; i<hungryWorkers; i++ ){
            m_resources[ 5 + rand()%5 ].addMutiny();
        }
        m_resources[ 0 ].setQuantity( 0 );
    }
    if( hungryWorkers > 0 ){
        std::cout << "Niestety " << hungryWorkers << " robotnik\242w nie otrzyma\210o zap\210aty i rozpocz\251\210o strajk!" << std::endl;
        std::cout << "Nie b\251d\245 oni generowa\206 przychod\242w w ci\245gu najbli\276szej tury :-(" << std::endl << "Zadbaj o wieksz\245 ilo\230\206 g\242rnik\242w!" << std::flush;
        Sleep( 3000 );
        system ( "clear || cls" );
    }
}

void ResourceManager::endMutiny()
{
    for( int i = 5; i <= 14; i++ )
        m_resources[ i ].setMutiny( 0 );
}

void ResourceManager::hungry()
{
    int hungryWorkers = 0;
    int workers = m_resources[ 5 ].getQuantity() + m_resources[ 6 ].getQuantity() + m_resources[ 7 ].getQuantity() + m_resources[ 8 ].getQuantity() + m_resources[ 9 ].getQuantity();

    //Losowi workers umieraj\245 z braku po\276ywienia
    if( workers <= m_resources[ 4 ].getQuantity() / ( 2 * ( m_tour / FACTOR + 1 ) ) )
        m_resources[ 4 ].substractResources( workers * 2 * ( m_tour / FACTOR + 1 ) );
    else{
        hungryWorkers = workers - m_resources[ 4 ].getQuantity() / ( 2 * ( m_tour / FACTOR + 1 ) );
        for( int i = 0; i < hungryWorkers; i++ ){
            while( !m_resources[ 5 + rand()%5 ].substractResources( 1 ) );
        }
        m_resources[ 4 ].setQuantity( 0 );
    }
    if( hungryWorkers > 0 ){
        std::cout << "Niestety " << hungryWorkers << " robotnik\242w umar\210o z g\210odu :-(" << std::endl << " Zadbaj o wi\251ksz\245 liczb\251 farmer\242w!" << std::flush;
        Sleep( 3000 );
        system ( "clear || cls" );
    }
}

void ResourceManager::breakdown()
{
    int a = 10 + rand()%5;
    if( m_resources[ a ].getQuantity() ){
        m_resources[ a ].setMutiny( 1 );
        std::cout << "Niestety nast\245pi\210a awaria ";
        switch( a )
        {
        case 10:
            std::cout << "kopalni";
            break;
        case 11:
            std::cout << "huty stali";
            break;
        case 12:
            std::cout << "tartaku";
            break;
        case 13:
            std::cout << "kamienio\210omu";
            break;
        case 14:
            std::cout << "farmy";
            break;
        }
        std::cout << "." << std::endl << "Przez t\245 tur\251 fabryka nie b\251dzie generowa\210a przychod\242w :-(" << std::flush;
        Sleep( 3000 );
        system( "clear || cls" );
    }
}

void ResourceManager::thiefs()
{
    int a = rand()%5;
    if( m_resources[ a ].getQuantity() > 0 ){
        int x = rand()%( m_resources[ a ].getQuantity() - 1 );
        m_resources[ a ].substractResources( x );
        std::cout << "Niestety z\210odzieje ukradli Ci " << x << " sztuk ";
        switch( a )
        {
        case 0:
            std::cout << "z\210ota :-( To pewnie ZUS, ale ciiii ;-)" << std::flush;
            break;
        case 1:
            std::cout << "stali :-(" << std::flush;
            break;
        case 2:
            std::cout << "drewna :-(" << std::flush;
            break;
        case 3:
            std::cout << "kamieni :-(" << std::flush;
            break;
        case 4:
            std::cout << "zwierzyny :-(" << std::flush;
            break;
        }
        Sleep( 2500 );
        system( "clear || cls" );
    }
}

void ResourceManager::miracle()
{
    int a = rand()%5;
    int x = rand()%( m_resources[ a ].getQuantity() );
    m_resources[ a ].addResources( x );
    std::cout << "Chyba zdarzy\210 si\251 cud, bo w twoim magazynie przyby\210o " << x << " sztuk ";
    switch( a )
    {
    case 0:
        std::cout << "z\210ota :-)" << std::flush;
        break;
    case 1:
        std::cout << "stali :-)" << std::flush;
        break;
    case 2:
        std::cout << "drewna :-)" << std::flush;
        break;
    case 3:
        std::cout << "kamieni :-)" << std::flush;
        break;
    case 4:
        std::cout << "zwierzyny :-)" << std::flush;
        break;
    }
    Sleep( 2500 );
    system( "clear || cls" );
}

void ResourceManager::destruction()
{
    int a = 10 + rand()%5;
    if( m_resources[ a ].getQuantity() > 0 ){
        m_resources[ a - 5 ].substractResources( m_resources[ a - 5 ].getQuantity() / m_resources[ a ].getQuantity() );
        m_resources[ a ].substractResources( 1 );
        std::cout << "Niestety ";
        switch( a )
        {
        case 10:
            std::cout << "w kopalni z\210ota zabrak\210o z\210ota i trzeba by\210o j\245 zamkn\245\206, a robotnicy z niej uciekli :-(" << std::flush;
            break;
        case 11:
            std::cout << "huta stali uleg\210a zniszczeniu, a robotnicy z niej uciekli :-(" << std::flush;
            break;
        case 12:
            std::cout << "tartak si\251 sfajczy\210 a razem z nim sfajczyli si\251 robotnicy :-(" << std::flush;
            break;
        case 13:
            std::cout << "z kamieno\210omu zosta\210 sam gruz, a pod gruzem rozgnieceni robotnicy :-(" << std::flush;
            break;
        case 14:
            std::cout << "na farm\251 spad\210a zaraza i trzeba by\210o j\245 zamkn\245\206. Zaraza spad\210a w r\242wnym stopni na robotnik\210w :-(" << std::flush;
            break;
        }
        Sleep( 2500 );
        system( "clear || cls" );
    }
}

void ResourceManager::buildFactory( int number )
{
    switch( number )
    {
    case 1:
        if( m_resources[ 1 ].getQuantity() >= 30 * ( m_tour / FACTOR + 1 ) && m_resources[ 2 ].getQuantity() >= 250 * ( m_tour / FACTOR + 1 ) && m_resources[ 3 ].getQuantity() >= 70 * ( m_tour / FACTOR + 1 ) ){
            m_resources[ 1 ].substractResources( 30 * ( m_tour / FACTOR + 1 ) );
            m_resources[ 2 ].substractResources( 250 * ( m_tour / FACTOR + 1 ) );
            m_resources[ 3 ].substractResources( 70 * ( m_tour / FACTOR + 1 ) );
            m_resources[ 10 ].addResources( 1 );
            std::cout << "Pomy\230lnie wybudowano kopalni\251 z\210ota :-)" << std::flush;
        }
        else
            std::cout << "Za ma\210o surowc\242w, aby zbudowa\206 kopalni\251 z\210ota :-(" << std::flush;
        break;
    case 2:
        if( m_resources[ 2 ].getQuantity() >= 100 * ( m_tour / FACTOR + 1 ) && m_resources[ 3 ].getQuantity() >= 100 * ( m_tour / FACTOR + 1 ) ){
            m_resources[ 2 ].substractResources( 100 * ( m_tour / FACTOR + 1 ) );
            m_resources[ 3 ].substractResources( 100 * ( m_tour / FACTOR + 1 ) );
            m_resources[ 11 ].addResources( 1 );
            std::cout << "Pomy\230lnie wybudowano hut\251 stali :-)" << std::flush;
        }
        else
            std::cout << "Za ma\210o surowc\242w, aby zbudowa\206 hut\251 stali :-(" << std::flush;
        break;
    case 3:
        if( m_resources[ 1 ].getQuantity() >= 100 * ( m_tour / FACTOR + 1 ) && m_resources[ 3 ].getQuantity() >= 50 * ( m_tour / FACTOR + 1 ) ){
            m_resources[ 1 ].substractResources( 100 * ( m_tour / FACTOR + 1 ) );
            m_resources[ 3 ].substractResources( 50 * ( m_tour / FACTOR + 1 ) );
            m_resources[ 12 ].addResources( 1 );
            std::cout << "Pomy\230lnie wybudowano tartak :-)" << std::flush;
        }
        else
            std::cout << "Za ma\210o surowc\242w, aby zbudowa\206 tartak :-(" << std::flush;
        break;
    case 4:
        if( m_resources[ 1 ].getQuantity() >= 30 * ( m_tour / FACTOR + 1 ) && m_resources[ 2 ].getQuantity() >= 400 * ( m_tour / FACTOR + 1 ) ){
            m_resources[ 1 ].substractResources( 30 * ( m_tour / FACTOR + 1 ) );
            m_resources[ 2 ].substractResources( 400 * ( m_tour / FACTOR + 1 ) );
            m_resources[ 13 ].addResources( 1 );
            std::cout << "Pomy\230lnie wybudowano kamienio\210om :-)" << std::flush;
        }
        else
            std::cout << "Za ma\210o surowc\242w, aby zbudowa\206 kamienio\210om :-(" << std::flush;
        break;
    case 5:
        if( m_resources[ 1 ].getQuantity() >= 20 * ( m_tour / FACTOR + 1 ) && m_resources[ 2 ].getQuantity() >= 200 * ( m_tour / FACTOR + 1 ) && m_resources[ 3 ].getQuantity() >= 25 * ( m_tour / FACTOR + 1 ) ){
            m_resources[ 1 ].substractResources( 20 * ( m_tour / FACTOR + 1 ) );
            m_resources[ 2 ].substractResources( 200 * ( m_tour / FACTOR + 1 ) );
            m_resources[ 3 ].substractResources( 25 * ( m_tour / FACTOR + 1 ) );
            m_resources[ 14 ].addResources( 1 );
            std::cout << "Pomy\230lnie wybudowano farm\251 :-)" << std::flush;
        }
        else
            std::cout << "Za ma\210o surowc\242w, aby zbudowa\206 farm\251 :-(" << std::flush;
        break;
    }
    Sleep( 2000 );
    system( "clear || cls" );
}

void ResourceManager::hireWorker( int number )
{
    int quantity;
    std::cout << "Ilu robotnik\242w chcesz zatrudni\206: ";
    std::cin >> quantity;
    if( !std::cin.good() ){
        std::cin.clear();
        std::cin.ignore( 100, '\n' );
    }
    if( quantity < 1 ) return;
    if( m_resources[ 9 + number ].getQuantity() * 5 < m_resources[ 4 + number ].getQuantity() + quantity )
        std::cout << "Nie masz wystarczaj\245co miejsc w fabrykach :-(" << std::endl << "Wybuduj nowe fabryki!" << std::flush;
    else{
        if( !m_resources[ 0 ].substractResources( quantity * ( m_tour / FACTOR + 1 ) ) )
            std::cout << "Nie masz wystarczaj\245co z\210ota na koncie!" << std::endl << "Zadbaj o wieksza\230\206 g\242rnik\242w!" << std::flush;
        else{
            m_resources[ 4 + number ].addResources( quantity );
            std::cout << "Zatrudni\210e\230 " << quantity << " robotnik\242w :-)" << std::flush;
        }
    }
    Sleep( 2000 );
    system( "clear || cls" );
}
