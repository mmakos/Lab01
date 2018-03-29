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
    m_resources[ 0 ] = Resource( "Zloto", 10 );       //0
    m_resources[ 1 ] = Resource( "Stal", 50 );           //1
    m_resources[ 2 ] = Resource( "Drewno", 300 );        //2
    m_resources[ 3 ] = Resource( "Kamien", 100 );     //3
    m_resources[ 4 ] = Resource( "Zwierzeta", 60 );   //4

    m_resources[ 5 ] = Resource( "Gornicy", 0 );      //5
    m_resources[ 6 ] = Resource( "Stalownicy", 0 );      //6
    m_resources[ 7 ] = Resource( "Drwale", 0 );          //7
    m_resources[ 8 ] = Resource( "Kamieniarze", 0 );     //8
    m_resources[ 9 ] = Resource( "Farmerzy", 0 );        //9

    m_resources[ 10 ] = Resource( "Kopalnie", 0 );        //10
    m_resources[ 11 ] = Resource( "Huty stali", 1 );      //11
    m_resources[ 12 ] = Resource( "Tartak", 1 );          //12
    m_resources[ 13 ] = Resource( "Kamieniolomy", 1 ); //13
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

    //Robotnicy, ktorzy nie dostali zlota rozpoczynaja strajk
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
        std::cout << "Niestety " << hungryWorkers << " robotnikow nie otrzymalo zaplaty i rozpoczelo strajk!" << std::endl;
        std::cout << "Nie beda oni generowac przychodow w ciagu najblizszej tury :-(" << std::endl << "Zadbaj o wieksza ilosc gornikow!" << std::flush;
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

    //Losowi workers umieraja z braku pozywienia
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
        std::cout << "Niestety " << hungryWorkers << " robotnikow umarlo z glodu :-(" << std::endl << " Zadbaj o wieksza liczbe farmerow!" << std::flush;
        Sleep( 3000 );
        system ( "clear || cls" );
    }
}

void ResourceManager::breakdown()
{
    int a = 10 + rand()%5;
    if( m_resources[ a ].getQuantity() ){
        m_resources[ a ].setMutiny( 1 );
        std::cout << "Niestety nastapila awaria ";
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
            std::cout << "kamieniolomu";
            break;
        case 14:
            std::cout << "farmy";
            break;
        }
        std::cout << "." << std::endl << "Przez ta ture fabryka nie bedzie generowala przychodow :-(" << std::flush;
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
        std::cout << "Niestety zlodzieje ukradli Ci " << x << " sztuk ";
        switch( a )
        {
        case 0:
            std::cout << "zlota :-( To pewnie ZUS, ale ciiii ;-)" << std::flush;
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
    std::cout << "Chyba zdarzyl sie cud, bo w twoim magazynie przybylo " << x << " sztuk ";
    switch( a )
    {
    case 0:
        std::cout << "zlota :-)" << std::flush;
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
            std::cout << "w kopalni zlota zabraklo zlota i trzeba bylo ja zamknac, a robotnicy z niej uciekli :-(" << std::flush;
            break;
        case 11:
            std::cout << "huta stali ulegla zniszczeniu, a robotnicy z niej uciekli :-(" << std::flush;
            break;
        case 12:
            std::cout << "tartak sie sfajczyl a razem z nim sfajczyli sie robotnicy :-(" << std::flush;
            break;
        case 13:
            std::cout << "z kamienolomu zostal sam gruz, a pod gruzem rozgnieceni robotnicy :-(" << std::flush;
            break;
        case 14:
            std::cout << "na farme spadla zaraza i trzeba bylo ja zamknac. Zaraza spadla w rownym stopni na robotniklw :-(" << std::flush;
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
            std::cout << "Pomyslnie wybudowano kopalnie zlota :-)" << std::flush;
        }
        else
            std::cout << "Za malo surowcow, aby zbudowac kopalnie zlota :-(" << std::flush;
        break;
    case 2:
        if( m_resources[ 2 ].getQuantity() >= 100 * ( m_tour / FACTOR + 1 ) && m_resources[ 3 ].getQuantity() >= 100 * ( m_tour / FACTOR + 1 ) ){
            m_resources[ 2 ].substractResources( 100 * ( m_tour / FACTOR + 1 ) );
            m_resources[ 3 ].substractResources( 100 * ( m_tour / FACTOR + 1 ) );
            m_resources[ 11 ].addResources( 1 );
            std::cout << "Pomyslnie wybudowano hute stali :-)" << std::flush;
        }
        else
            std::cout << "Za malo surowcow, aby zbudowac hute stali :-(" << std::flush;
        break;
    case 3:
        if( m_resources[ 1 ].getQuantity() >= 100 * ( m_tour / FACTOR + 1 ) && m_resources[ 3 ].getQuantity() >= 50 * ( m_tour / FACTOR + 1 ) ){
            m_resources[ 1 ].substractResources( 100 * ( m_tour / FACTOR + 1 ) );
            m_resources[ 3 ].substractResources( 50 * ( m_tour / FACTOR + 1 ) );
            m_resources[ 12 ].addResources( 1 );
            std::cout << "Pomyslnie wybudowano tartak :-)" << std::flush;
        }
        else
            std::cout << "Za malo surowcow, aby zbudowac tartak :-(" << std::flush;
        break;
    case 4:
        if( m_resources[ 1 ].getQuantity() >= 30 * ( m_tour / FACTOR + 1 ) && m_resources[ 2 ].getQuantity() >= 400 * ( m_tour / FACTOR + 1 ) ){
            m_resources[ 1 ].substractResources( 30 * ( m_tour / FACTOR + 1 ) );
            m_resources[ 2 ].substractResources( 400 * ( m_tour / FACTOR + 1 ) );
            m_resources[ 13 ].addResources( 1 );
            std::cout << "Pomyslnie wybudowano kamieniolom :-)" << std::flush;
        }
        else
            std::cout << "Za malo surowcow, aby zbudowac kamieniolom :-(" << std::flush;
        break;
    case 5:
        if( m_resources[ 1 ].getQuantity() >= 20 * ( m_tour / FACTOR + 1 ) && m_resources[ 2 ].getQuantity() >= 200 * ( m_tour / FACTOR + 1 ) && m_resources[ 3 ].getQuantity() >= 25 * ( m_tour / FACTOR + 1 ) ){
            m_resources[ 1 ].substractResources( 20 * ( m_tour / FACTOR + 1 ) );
            m_resources[ 2 ].substractResources( 200 * ( m_tour / FACTOR + 1 ) );
            m_resources[ 3 ].substractResources( 25 * ( m_tour / FACTOR + 1 ) );
            m_resources[ 14 ].addResources( 1 );
            std::cout << "Pomyslnie wybudowano farme :-)" << std::flush;
        }
        else
            std::cout << "Za malo surowcow, aby zbudowac farme :-(" << std::flush;
        break;
    }
    Sleep( 2000 );
    system( "clear || cls" );
}

void ResourceManager::hireWorker( int number )
{
    int quantity;
    std::cout << "Ilu robotnikow chcesz zatrudnic: ";
    std::cin >> quantity;
    if( !std::cin.good() ){
        std::cin.clear();
        std::cin.ignore( 100, '\n' );
    }
    if( quantity < 1 ) return;
    if( m_resources[ 9 + number ].getQuantity() * 5 < m_resources[ 4 + number ].getQuantity() + quantity )
        std::cout << "Nie masz wystarczajaco miejsc w fabrykach :-(" << std::endl << "Wybuduj nowe fabryki!" << std::flush;
    else{
        if( !m_resources[ 0 ].substractResources( quantity * ( m_tour / FACTOR + 1 ) ) )
            std::cout << "Nie masz wystarczajaco zlota na koncie!" << std::endl << "Zadbaj o wiekszasc gornikow!" << std::flush;
        else{
            m_resources[ 4 + number ].addResources( quantity );
            std::cout << "Zatrudniles " << quantity << " robotnikow :-)" << std::flush;
        }
    }
    Sleep( 2000 );
    system( "clear || cls" );
}
